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

#include "transformer.hpp"

namespace cpd {

Transformer::Transformer(double epsilon, double breakpoint)
    : m_epsilon(epsilon), m_breakpoint(breakpoint) {}

Vector Transformer::fgt(const MatrixRef source, const MatrixRef target,
                        double bandwidth) const {
    if (bandwidth > breakpoint()) {
        return fgt::ifgt(source, target, bandwidth, epsilon());
    } else {
        return fgt::direct_tree(source, target, bandwidth, epsilon());
    }
}

Vector Transformer::fgt(const MatrixRef source, const MatrixRef target,
                        double bandwidth, const VectorRef weights) const {
    if (bandwidth > breakpoint()) {
        return fgt::ifgt(source, target, bandwidth, epsilon(), weights);
    } else {
        return fgt::direct_tree(source, target, bandwidth, epsilon(), weights);
    }
}

void Transformer::precompute(const MatrixRef source, double bandwidth) {
    if (bandwidth > breakpoint()) {
        m_transform.reset(new fgt::Ifgt(source, bandwidth, epsilon()));
    } else {
        m_transform.reset(new fgt::DirectTree(source, bandwidth, epsilon()));
    }
}

Vector Transformer::fgt_precomputed(const MatrixRef target,
                                    const VectorRef weights) const {
    assert(m_transform);
    return m_transform->compute(target, weights);
}
}
