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

#include "transformer.hpp"
#include "utils.hpp"

namespace cpd {

Matrix construct_affinity_matrix(const MatrixRef X, const MatrixRef Y,
                                 double beta) {
    assert(X.cols() == Y.cols());
    double k = -2.0 * beta * beta;
    unsigned long N = X.rows();
    unsigned long M = Y.rows();
    Matrix G(N, M);
    for (size_t i = 0; i < M; ++i) {
        G.col(i) = ((X.array() - Y.row(i).replicate(N, 1).array())
                        .pow(2)
                        .rowwise()
                        .sum() /
                    k).exp();
    }
    return G;
}

std::tuple<Vector, Vector, Matrix, double>
calculate_probabilities(const MatrixRef X, const MatrixRef Y, double sigma2,
                        double outliers, double fgt_epsilon, double fgt_breakpoint) {
    assert(X.cols() == Y.cols());
    unsigned long N = X.rows();
    unsigned long M = Y.rows();
    unsigned long D = X.cols();
    Transformer transformer(fgt_epsilon, fgt_breakpoint);
    double hsigma = std::sqrt(2.0 * sigma2);
    Vector Kt1 = transformer.fgt(Y, X, hsigma);
    double ndi = outliers / (1 - outliers) * M / N *
                 std::pow(2.0 * M_PI * sigma2, 0.5 * double(D));
    Eigen::ArrayXd denomP = Kt1.array() + ndi;
    Vector Pt1 = 1 - ndi / denomP;
    transformer.precompute(X, hsigma);
    Vector P1 = transformer.fgt_precomputed(Y, 1 / denomP);
    Matrix PX(M, D);
    for (size_t i = 0; i < D; ++i) {
        PX.col(i) = transformer.fgt_precomputed(Y, X.col(i).array() / denomP);
    }
    double L = -denomP.log().sum() + D * N * std::log(sigma2) / 2.0;
    return std::make_tuple(Pt1, P1, PX, L);
}
}
