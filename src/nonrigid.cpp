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

#include <Eigen/QR>
#include <Eigen/Sparse>

#include <cpd/nonrigid.hpp>

#include "registration_impl.hpp"
#include "utils.hpp"

namespace cpd {

Nonrigid::Nonrigid()
    : Registration(),
      m_beta(Nonrigid::DEFAULT_BETA),
      m_lambda(Nonrigid::DEFAULT_LAMBDA) {}

NonrigidResult Nonrigid::compute_impl(const MatrixRef X, const MatrixRef Y,
                                      double sigma2) {
    assert(X.cols() == Y.cols());

    auto M = Y.rows();
    auto D = Y.cols();
    Matrix T = Y;
    size_t max_iter = this->max_iterations();
    size_t iter = 0;
    double tol = this->tolerance();
    double ntol = std::numeric_limits<double>::max();
    double L = 1.0;
    Matrix W = Matrix::Zero(M, D);
    double beta = this->beta();
    double lambda = this->lambda();
    Vector Pt1;
    Vector P1;
    Matrix PX;

    Matrix G = construct_affinity_matrix(Y, Y, beta);

    while (iter < max_iter && ntol > tol &&
           sigma2 > 10 * std::numeric_limits<double>::epsilon()) {
        double L_old = L;
        std::tie(Pt1, P1, PX, L) = calculate_probabilities(X, T, sigma2);
        L = L + lambda / 2 * (W.transpose() * G * W).trace();
        ntol = std::abs((L - L_old) / L);

        // TODO this shouldn't be cout
        std::cout << "CPD Nonrigid (FGT) : dL= " << ntol << ", iter= " << iter
                  << ", sigma2= " << sigma2;

        auto dP = P1.asDiagonal();
        W = (dP * G + lambda * sigma2 * Matrix::Identity(M, M))
                .colPivHouseholderQr()
                .solve(PX - dP * Y);

        T = Y + G * W;
        double Np = P1.sum();
        sigma2 =
            std::abs(((X.array().pow(2) * Pt1.replicate(1, D).array()).sum() +
                      (T.array().pow(2) * P1.replicate(1, D).array()).sum() -
                      2 * (PX.transpose() * T).trace()) /
                     (Np * D));

        ++iter;
    }

    return {T};
}

NonrigidResult nonrigid(const MatrixRef source, const MatrixRef target) {
    return Nonrigid().compute(source, target);
}

NonrigidResult nonrigid(const MatrixRef source, const MatrixRef target,
                        double sigma2) {
    return Nonrigid().compute(source, target, sigma2);
}

template class Registration<NonrigidResult>;
}
