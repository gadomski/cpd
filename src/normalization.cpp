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
Normalization::Normalization(const MatrixRef source, const MatrixRef target)
    : m_translation_x(source.colwise().mean()),
      m_translation_y(target.colwise().mean()) {
    auto x = source - m_translation_x.replicate(source.rows(), 1);
    auto y = target - m_translation_y.replicate(target.rows(), 1);
    m_scaling = std::max(std::sqrt(x.array().pow(2).sum() / source.rows()),
                         std::sqrt(y.array().pow(2).sum() / target.rows()));
    m_source = x / m_scaling;
    m_target = y / m_scaling;
}
}
