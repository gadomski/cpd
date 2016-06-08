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

#include "normalization.hpp"

namespace cpd {
Normalization::Normalization(const MatrixRef fixed, const MatrixRef moving)
    : m_translation_x(fixed.colwise().mean()),
      m_translation_y(moving.colwise().mean()) {
    auto x = fixed - m_translation_x.replicate(fixed.rows(), 1);
    auto y = moving - m_translation_y.replicate(moving.rows(), 1);
    m_scaling = std::max(std::sqrt(x.array().pow(2).sum() / fixed.rows()),
                         std::sqrt(y.array().pow(2).sum() / moving.rows()));
    m_fixed = x / m_scaling;
    m_moving = y / m_scaling;
}
}
