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

#include <cmath>

#include <cpd/registration.hpp>

namespace cpd {

template <typename T>
std::tuple<Vector, Vector, Matrix, double>
Registration<T>::calculate_probabilities(const MatrixRef X, const MatrixRef Y,
                                         double sigma2) const {
    assert(X.cols() == Y.cols());
    auto N = X.rows();
    auto M = Y.rows();
    auto D = X.cols();
    if (use_fgt()) {
        double hsigma = std::sqrt(2.0 * sigma2);
        std::unique_ptr<fgt::Transform> transform;
        std::function<void(const MatrixRef)> reset_transform = [&](
            const MatrixRef matrix) {
            if (hsigma > fgt_breakpoint()) {
                transform.reset(new fgt::Ifgt(matrix, hsigma, fgt_epsilon()));
            } else {
                transform.reset(
                    new fgt::DirectTree(matrix, hsigma, fgt_epsilon()));
            }
        };
        reset_transform(Y);
        Vector Kt1 = transform->compute(X);
        double ndi = outlier_weight() / (1 - outlier_weight()) * M / N *
                     std::pow(2.0 * M_PI * sigma2, 0.5 * double(D));
        Eigen::ArrayXd denomP = Kt1.array() + ndi;
        Vector Pt1 = 1 - ndi / denomP;
        reset_transform(X);
        Vector P1 = transform->compute(Y, 1 / denomP);
        Matrix PX(M, D);
        for (size_t i = 0; i < D; ++i) {
            PX.col(i) = transform->compute(Y, X.col(i).array() / denomP);
        }
        double L = -denomP.log().sum() + D * N * std::log(sigma2) / 2.0;
        return std::make_tuple(Pt1, P1, PX, L);
    } else {
        Vector P(M);
        Vector Pt1(N);
        Vector P1 = Vector::Zero(M);
        Matrix PX = Matrix::Zero(M, D);
        double E = 0.0;
        double ksig = -2.0 * sigma2;
        double outlier_tmp = outlier_weight() * M *
                             std::pow(-ksig * M_PI, 0.5 * D) /
                             ((1 - outlier_weight()) * N);

        for (size_t n = 0; n < N; ++n) {
            double sp = 0;
            for (size_t m = 0; m < M; ++m) {
                double razn = (X.row(n) - Y.row(m)).array().pow(2).sum();
                P(m) = std::exp(razn / ksig);
                sp += P(m);
            }
            sp += outlier_tmp;
            Pt1(n) = 1 - outlier_tmp / sp;
            Vector temp_x = X.row(n) / sp;
            for (size_t m = 0; m < M; ++m) {
                P1(m) += P(m) / sp;
                PX.row(m) += temp_x * P(m);
            }
            E += std::log(sp);
        }
        E += D * N * std::log(sigma2) / 2;
        return std::make_tuple(Pt1, P1, PX, E);
    }
}
}
