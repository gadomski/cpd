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

#include <cpd/normalize.hpp>

namespace cpd {

Normalization normalize(const Matrix& fixed, const Matrix& moving) {
    Normalization normalization;
    normalization.fixed_mean = fixed.colwise().mean();
    normalization.fixed =
        fixed - normalization.fixed_mean.transpose().replicate(fixed.rows(), 1);
    normalization.moving_mean = moving.colwise().mean();
    normalization.moving =
        moving -
        normalization.moving_mean.transpose().replicate(moving.rows(), 1);
    double fixed_scale =
        std::sqrt(normalization.fixed.array().pow(2).sum() / fixed.rows());
    double moving_scale =
        std::sqrt(normalization.moving.array().pow(2).sum() / moving.rows());
    normalization.scale = std::max(fixed_scale, moving_scale);
    normalization.fixed /= normalization.scale;
    normalization.moving /= normalization.scale;
    return normalization;
}
}
