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

#include "cpd/affine.hpp"
#include "cpd/runner.hpp"

namespace cpd {

Affine::Result affine(const Matrix& fixed, const Matrix& moving) {
    return run<Affine>(fixed, moving);
}

Affine::Result Affine::compute(const Matrix& fixed, const Matrix& moving,
                               const Probabilities& probabilities,
                               double sigma2) const {
    double np = probabilities.p1.sum();
    Vector mu_x = fixed.transpose() * probabilities.pt1 / np;
    Vector mu_y = moving.transpose() * probabilities.p1 / np;
    Matrix b1 =
        probabilities.px.transpose() * moving - np * mu_x * mu_y.transpose();
    Matrix b2 =
        (moving.array() * probabilities.p1.replicate(1, moving.cols()).array())
                .transpose()
                .matrix() *
            moving -
        np * mu_y * mu_y.transpose();
    Affine::Result result;
    result.transform = b1 * b2.inverse();
    result.translation = mu_x - result.transform * mu_y;
    result.sigma2 =
        std::abs((fixed.array().pow(2) *
                  probabilities.pt1.replicate(1, fixed.cols()).array())
                     .sum() -
                 np * mu_x.transpose() * mu_x -
                 (b1 * result.transform.transpose()).trace()) /
        (np * fixed.cols());
    result.points = moving * result.transform.transpose() +
                    result.translation.transpose().replicate(moving.rows(), 1);
    return result;
}

void Affine::denormalize(const Normalization& normalization,
                         Result& result) const {
    result.translation = normalization.scale * result.translation +
                         normalization.fixed_mean -
                         result.transform * normalization.moving_mean;
    result.points =
        result.points * normalization.scale +
        normalization.fixed_mean.transpose().replicate(result.points.rows(), 1);
    return;
}
}
