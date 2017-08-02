// cpd - Coherent Point Drift
// Copyright (C) 2017 Pete Gadomski <pete.gadomski@gmail.com>
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

#include <cpd/gauss_transform_fgt.hpp>
#include <cmath>

namespace cpd {
std::unique_ptr<GaussTransform> GaussTransform::make_default() {
    return std::unique_ptr<GaussTransform>(new GaussTransformFgt());
}

Probabilities GaussTransformFgt::compute(const Matrix& fixed,
                                         const Matrix& moving, double sigma2,
                                         double outliers) const {
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

std::unique_ptr<fgt::Transform> GaussTransformFgt::create_transform(
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
}
} // namespace cpd
