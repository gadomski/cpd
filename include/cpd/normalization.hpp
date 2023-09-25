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

/// \file
///
/// Utility to scale/offset points to (roughly) conform to unit shape centered
/// at zero.

#pragma once

#include <cpd/matrix.hpp>

namespace cpd {

/// The results of normalizing data to a unit cube (or whatever dimensionality).
template <typename M, typename V>
struct Normalization {
    /// The average of the fixed points, that was subtracted from those data.
    V fixed_mean;
    /// The fixed points.
    M fixed;
    /// The scaling factor for the fixed points.
    typename M::Scalar fixed_scale;
    /// The average of the moving points, that was subtracted from those data.
    V moving_mean;
    /// The moving points.
    M moving;
    /// The scaling factor for the moving points.
    typename M::Scalar moving_scale;

    /// Creates a new normalization for the provided matrices.
    ///
    /// If `linked = true`, apply the same scaling to both sets of points. This
    /// is recommended if you are working with data that should not be scaled,
    /// e.g. LiDAR data. If `linked = false`, each point set is scaled
    /// seperately.
    ///
    /// Myronenko's original implementation only had `linked = false` logic.
    Normalization(const M& fixed, const M& moving, bool linked = true);
};
} // namespace cpd
