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

#pragma once

#include <fgt.hpp>

#include "cpd/matrix.hpp"

namespace cpd {

/// Class for managing fast Gauss transforms.
///
/// Since we want to break between direct_tree and ifgt Gauss transforms at a
/// certain point, it helps to have a class to manage that breakpoint.
/// This class also lets us store pre-computed clusterings for multiple runs.
class Transformer {
public:
    /// Creates a new transformer with specified parameters.
    Transformer(double epsilon, double breakpoint);

    /// Returns the error tolerance for this transformer.
    double epsilon() const { return m_epsilon; }
    /// Returns the breakpoint, when we switch from ifgt to direct_tree.
    double breakpoint() const { return m_breakpoint; }

    /// Computes the fgt for a given dataset.
    Vector fgt(const MatrixRef source, const MatrixRef target,
               double bandwidth) const;

    /// Computes the fgt for a given dataset, with weights
    Vector fgt(const MatrixRef source, const MatrixRef target, double bandwidth,
               const VectorRef weights) const;

    /// Precomputes clustering information for the given source and bandwidth.
    ///
    /// Use with `fgt_precomputed`.
    void precompute(const MatrixRef source, double bandwidth);

    /// Computes the fgt for the given dataset, using the precomputed transform.
    Vector fgt_precomputed(const MatrixRef target,
                           const VectorRef weights) const;

private:
    double m_epsilon;
    double m_breakpoint;
    std::unique_ptr<fgt::Transform> m_transform;
};
}
