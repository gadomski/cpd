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

#define _USE_MATH_DEFINES
#include <cmath>

#include "probability_calculator.hpp"

namespace cpd {

ProbabilityCalculator::ProbabilityCalculator(double outliers, double epsilon,
                                             double breakpoint)
    : m_outliers(outliers), m_epsilon(epsilon), m_breakpoint(breakpoint) {}

std::tuple<Vector, Vector, Matrix, double>
ProbabilityCalculator::calculate(const MatrixRef X, const MatrixRef Y,
                                 double sigma2) {
    assert(X.cols() == Y.cols());
    unsigned long N = X.rows();
    unsigned long M = Y.rows();
    unsigned long D = X.cols();
    double hsigma = std::sqrt(2.0 * sigma2);
    std::unique_ptr<fgt::Transform> transform;
    std::function<void(const MatrixRef)> reset_transform =
        [&](const MatrixRef matrix) {
            if (hsigma > m_breakpoint) {
                transform.reset(new fgt::Ifgt(matrix, hsigma, m_epsilon));
            } else {
                transform.reset(new fgt::DirectTree(matrix, hsigma, m_epsilon));
            }
        };
    reset_transform(Y);
    Vector Kt1 = transform->compute(X);
    double ndi = m_outliers / (1 - m_outliers) * M / N *
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
}
}
