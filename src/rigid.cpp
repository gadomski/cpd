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

#include "cpd/rigid.hpp"
#include "cpd/probabilities.hpp"
#include "cpd/runner.hpp"

namespace cpd {

Rigid::Result Rigid::compute(const Matrix& fixed, const Matrix& moving,
                             const Probabilities& probabilities, double) const {
    size_t cols = fixed.cols();
    double np = probabilities.pt1.sum();
    Vector mu_x = fixed.transpose() * probabilities.pt1 / np;
    Vector mu_y = moving.transpose() * probabilities.p1 / np;
    Matrix a =
        probabilities.px.transpose() * moving - np * mu_x * mu_y.transpose();
    Eigen::JacobiSVD<Matrix, Eigen::NoQRPreconditioner> svd(
        a, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Matrix s = svd.singularValues().asDiagonal();
    Matrix c = Matrix::Identity(cols, cols);
    if (!m_allow_reflections) {
        c(cols - 1, cols - 1) =
            (svd.matrixU() * svd.matrixV().transpose()).determinant();
    }
    Rigid::Result result;
    result.rotation = svd.matrixU() * c * svd.matrixV().transpose();
    if (m_scale) {
        result.scale =
            (s * c).trace() / ((moving.array().pow(2) *
                                probabilities.p1.replicate(1, cols).array())
                                   .sum() -
                               np * mu_y.transpose() * mu_y);
        result.sigma2 = std::abs(((fixed.array().pow(2) *
                                   probabilities.pt1.replicate(1, cols).array())
                                      .sum()) -
                                 np * mu_x.transpose() * mu_x -
                                 result.scale * (s * c).trace()) /
                        (np * cols);
    } else {
        result.scale = 1.0;
        result.sigma2 =
            std::abs(((fixed.array().pow(2) *
                       probabilities.pt1.replicate(1, cols).array())
                          .sum() +
                      (moving.array().pow(2) *
                       probabilities.p1.replicate(1, cols).array())
                          .sum() -
                      np * mu_x.transpose() * mu_x -
                      np * mu_y.transpose() * mu_y - 2 * (s * c).trace())) /
            (np * cols);
    }
    result.translation = mu_x - result.scale * result.rotation * mu_y;
    result.points = result.scale * moving * result.rotation.transpose() +
                    result.translation.transpose().replicate(moving.rows(), 1);
    return result;
}

void Rigid::denormalize(const Normalization& normalization,
                        Rigid::Result& result) const {
    result.translation =
        normalization.scale * result.translation + normalization.fixed_mean -
        result.scale * result.rotation * normalization.moving_mean;
    result.points =
        result.points * normalization.scale +
        normalization.fixed_mean.transpose().replicate(result.points.rows(), 1);
}

Rigid::Result rigid(const Matrix& fixed, const Matrix& moving) {
    return run<Rigid>(fixed, moving);
}

std::ostream& operator<<(std::ostream& stream, const Rigid::Result& result) {
    Eigen::IOFormat json_format(Eigen::StreamPrecision, 0, ", ", ",", "[", "]",
                                "[", "]");
    stream << "{\n"
           << "    \"translation\": "
           << result.translation.transpose().format(json_format)
           << ",\n    \"rotation\": "
           << result.rotation.transpose().format(json_format)
           << ",\n    \"scale\": " << result.scale << "\n}";
    return stream;
}
}
