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

#include "cpd/comparer.hpp"

namespace cpd {

Probabilities DirectComparer::compute(const Matrix& fixed, const Matrix& moving,
                                      double sigma2, double outliers) const {
    double ksig = -2.0 * sigma2;
    size_t cols = fixed.cols();
    double outlier_tmp =
        (outliers * moving.rows() * std::pow(-ksig * M_PI, 0.5 * cols)) /
        ((1 - outliers) * fixed.rows());
    Vector p = Vector::Zero(moving.rows());
    Vector p1 = Vector::Zero(moving.rows());
    Vector p1_max = Vector::Zero(moving.rows());
    Vector pt1 = Vector::Zero(fixed.rows());
    Matrix px = Matrix::Zero(moving.rows(), cols);
    IndexVector correspondence = IndexVector::Zero(moving.rows());
    double l = 0.0;

    for (Matrix::Index i = 0; i < fixed.rows(); ++i) {
        double sp = 0;
        for (Matrix::Index j = 0; j < moving.rows(); ++j) {
            double razn = (fixed.row(i) - moving.row(j)).array().pow(2).sum();
            p(j) = std::exp(razn / ksig);
            sp += p(j);
        }
        sp += outlier_tmp;
        pt1(i) = 1 - outlier_tmp / sp;
        for (Matrix::Index j = 0; j < moving.rows(); ++j) {
            p1(j) += p(j) / sp;
            px.row(j) += fixed.row(i) * p(j) / sp;
            if (p(j) / sp > p1_max(j)) {
                correspondence(j) = i;
                p1_max(j) = p(j) / sp;
            }
        }
        l += -std::log(sp);
    }
    l += cols * fixed.rows() * std::log(sigma2) / 2;
    return { p1, pt1, px, l, correspondence };
}

std::unique_ptr<fgt::Transform> FgtComparer::create_transform(
    const Matrix& points, double bandwidth) const {
    switch (m_method) {
        case FgtMethod::DirectTree:
            return std::unique_ptr<fgt::Transform>(
                new fgt::DirectTree(points, bandwidth, m_epsilon));
        case FgtMethod::Ifgt:
            return std::unique_ptr<fgt::Transform>(
                new fgt::Ifgt(points, bandwidth, m_epsilon));
        case FgtMethod::Switched:
            if (bandwidth > m_breakpoint) {
                return std::unique_ptr<fgt::Transform>(
                    new fgt::Ifgt(points, bandwidth, m_epsilon));
            } else {
                return std::unique_ptr<fgt::Transform>(
                    new fgt::DirectTree(points, bandwidth, m_epsilon));
            }
    }
    return std::unique_ptr<fgt::Transform>();
}

Probabilities FgtComparer::compute(const Matrix& fixed, const Matrix& moving,
                                   double sigma2, double outliers) const {
    double bandwidth = std::sqrt(2.0 * sigma2);
    size_t cols = fixed.cols();
    std::unique_ptr<fgt::Transform> transform =
        create_transform(moving, bandwidth);
    auto kt1 = transform->compute(fixed);
    double ndi = outliers / (1.0 - outliers) * moving.rows() / fixed.rows() *
                 std::pow(2.0 * M_PI * sigma2, 0.5 * cols);
    Array denom_p = kt1.array() + ndi;
    Vector pt1 = 1 - ndi / denom_p;
    transform = create_transform(fixed, bandwidth);
    Vector p1 = transform->compute(moving, 1 / denom_p);
    Matrix px(moving.rows(), cols);
    for (size_t i = 0; i < cols; ++i) {
        px.col(i) = transform->compute(moving, fixed.col(i).array() / denom_p);
    }
    double l =
        -denom_p.log().sum() + cols * fixed.rows() * std::log(sigma2) / 2;
    return { p1, pt1, px, l };
}
}
