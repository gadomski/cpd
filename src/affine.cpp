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

#include <cpd/affine.hpp>

#include "registration_impl.hpp"

namespace cpd {

RigidResult Affine::compute_impl(const MatrixRef X, const MatrixRef Y,
                                 double sigma2) {
    assert(X.cols() == Y.cols());

    auto D = X.cols();
    auto M = Y.rows();
    size_t max_iter = this->max_iterations();
    size_t iter = 0;
    double tol = this->tolerance();
    double ntol = std::numeric_limits<double>::max();
    double L = 0.0;
    Vector t(D);
    Matrix T = Y;
    Matrix B(D, D);
    Vector Pt1;
    Vector P1;
    Matrix PX;

    while (iter < max_iter && ntol > tol &&
           sigma2 > 10 * std::numeric_limits<double>::epsilon()) {
        double L_old = L;

        std::tie(Pt1, P1, PX, L) = calculate_probabilities(X, T, sigma2);
        ntol = std::abs((L - L_old) / L);

        // TODO this shouldn't be cout
        std::cout << "CPD Affine (FGT) : dL= " << ntol << ", iter= " << iter
                  << ", sigma2= " << sigma2 << "\n";

        double Np = P1.sum();
        Vector mu_x = X.transpose() * Pt1 / Np;
        Vector mu_y = Y.transpose() * P1 / Np;

        Matrix B1 = PX.transpose() * Y - Np * mu_x * mu_y.transpose();
        Matrix B2 =
            (Y.array() * P1.replicate(1, D).array()).matrix().transpose() * Y -
            Np * (mu_y * mu_y.transpose());
        B = B2.transpose()
                .colPivHouseholderQr()
                .solve(B1.transpose())
                .transpose();
        t = mu_x - B * mu_y;
        T = Y * B.transpose() + t.transpose().replicate(M, 1);
        sigma2 =
            std::abs((X.array().pow(2) * Pt1.replicate(1, D).array()).sum() -
                     Np * mu_x.transpose() * mu_x -
                     (B1 * B.transpose()).trace()) /
            (Np * D);
        ++iter;
    }
    return {T, B, t, 1.0};
}

RigidResult affine(const MatrixRef source, const MatrixRef target) {
    return Affine().compute(source, target);
}

RigidResult affine(const MatrixRef source, const MatrixRef target,
                   double sigma2) {
    return Affine().compute(source, target, sigma2);
}
}
