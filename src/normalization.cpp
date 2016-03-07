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

#include "cpd/nonrigid.hpp"
#include "cpd/normalization.hpp"
#include "cpd/rigid.hpp"

#include <iostream>

namespace cpd {
Normalization::Normalization(const MatrixRef source, const MatrixRef target,
                             double sigma2) {
    auto N = source.rows();
    auto M = target.rows();
    m_translation = source.colwise().minCoeff().array().min(
        target.colwise().minCoeff().array());
    m_scaling = (source - m_translation.replicate(N, 1))
                    .colwise()
                    .maxCoeff()
                    .array()
                    .max((target - m_translation.replicate(M, 1))
                             .colwise()
                             .maxCoeff()
                             .array())
                    .maxCoeff();
    m_source = (source - m_translation.replicate(N, 1)) / m_scaling;
    m_target = (target - m_translation.replicate(M, 1)) / m_scaling;
    m_sigma2 = sigma2 / m_scaling;
}
}
