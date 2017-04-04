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

#include <cpd/normalization.hpp>

namespace cpd {

Normalization::Normalization(const Matrix& f, const Matrix& m, bool linked)
  : fixed_mean(f.colwise().mean())
  , fixed(f - fixed_mean.transpose().replicate(f.rows(), 1))
  , fixed_scale(std::sqrt(fixed.array().pow(2).sum() / fixed.rows()))
  , moving_mean(m.colwise().mean())
  , moving(m - moving_mean.transpose().replicate(m.rows(), 1))
  , moving_scale(std::sqrt(moving.array().pow(2).sum() / moving.rows())) {
    if (linked) {
        double scale = std::max(fixed_scale, moving_scale);
        fixed_scale = scale;
        moving_scale = scale;
    }
    fixed /= fixed_scale;
    moving /= moving_scale;
}
} // namespace cpd
