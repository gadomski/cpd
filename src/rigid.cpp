// cpd - Coherent Point Drift
// Copyright (C) 2016 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <Eigen/LU>
#include <Eigen/SVD>

#include <cpd/rigid.hpp>

#include "registration_impl.hpp"
#include "utils.hpp"

namespace cpd {

RigidResult rigid(const MatrixRef X, const MatrixRef Y) {
    return Rigid().compute(X, Y);
}

RigidResult rigid(const MatrixRef X, const MatrixRef Y, double sigma2) {
    return Rigid().compute(X, Y, sigma2);
}

Rigid::Rigid()
    : Registration<RigidResult>(),
      m_no_reflections(Rigid::DEFAULT_NO_REFLECTIONS),
      m_allow_scaling(Rigid::DEFAULT_ALLOW_SCALING) {}

RigidResult Rigid::compute_impl(const MatrixRef X, const MatrixRef Y,
                                double sigma2) {
    assert(X.cols() == Y.cols());

    unsigned long M = Y.rows();
    unsigned long D = X.cols();
    Matrix T = Y;
    double s = 1.0;
    Matrix R = Matrix::Identity(D, D);
    Vector t(D);
    size_t max_iter = this->max_iterations();
    size_t iter = 0;
    double tol = this->tolerance();
    double ntol = std::numeric_limits<double>::max();
    double L = 0.0;
    bool no_reflections = this->no_reflections();
    bool scale = this->allow_scaling();
    Vector Pt1;
    Vector P1;
    Matrix PX;

    while (iter < max_iter && ntol > tol &&
           sigma2 > 10 * std::numeric_limits<double>::epsilon()) {
        double L_old = L;
        // TODO myronenko has a sigma2 floor, which we may need for real
        // datasets

        std::tie(Pt1, P1, PX, L) = calculate_probabilities(X, T, sigma2);
        ntol = std::abs((L - L_old) / L);

        log()->info() << "CPD Rigid (FGT) : dL= " << ntol << ", iter= " << iter
                      << ", sigma2= " << sigma2;

        double Np = Pt1.sum();
        Vector mu_x = X.transpose() * Pt1 / Np;
        Vector mu_y = Y.transpose() * P1 / Np;
        Matrix A = PX.transpose() * Y - Np * mu_x * mu_y.transpose();
        Eigen::JacobiSVD<Matrix, Eigen::NoQRPreconditioner> svd(
            A, Eigen::ComputeThinU | Eigen::ComputeThinV);
        Matrix S = svd.singularValues().asDiagonal();
        Matrix C = Matrix::Identity(D, D);

        if (no_reflections) {
            C(D - 1, D - 1) =
                (svd.matrixU() * svd.matrixV().transpose()).determinant();
        }
        R = svd.matrixU() * C * svd.matrixV();

        if (scale) {
            s = (S * C).trace() /
                    (Y.array().pow(2) * P1.replicate(1, D).array()).sum() -
                Np * mu_y.transpose() * mu_y;
            sigma2 = ((X.array().pow(2) * Pt1.replicate(1, D).array()).sum() -
                      Np * mu_x.transpose() * mu_x - s * (S * C).trace()) /
                     (Np * D);
        } else {
            sigma2 = ((X.array().pow(2) * Pt1.replicate(1, D).array()).sum() +
                      (Y.array().pow(2) * P1.replicate(1, D).array()).sum() -
                      Np * mu_x.transpose() * mu_x -
                      Np * mu_y.transpose() * mu_y - 2 * (S * C).trace()) /
                     (Np * D);
        }

        t = mu_x - s * R * mu_y;
        T = s * Y * R.transpose() + t.transpose().replicate(M, 1);
        ++iter;
    }
    return {T, R, t, s};
}

template <>
RigidResult Normalization::denormalize(const RigidResult& result) const {
    RigidResult out(result);
    out.points = result.points * m_scaling +
                 m_translation.replicate(result.points.rows(), 1);
    out.translation =
        m_scaling * result.translation + m_translation.transpose() -
        result.scaling * result.rotation * m_translation.transpose();
    return out;
}
}
