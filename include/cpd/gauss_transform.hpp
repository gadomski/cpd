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
/// Basic correspondence/error calculation between two datasets, using the
/// direct method of the Gauss transform.

#pragma once

#include <cpd/matrix.hpp>
#include <memory>

namespace cpd {

/// Probability matrices produced by comparing two data sets with a
/// `GaussTransform`.
template <typename M, typename V>
struct Probabilities {
    /// The probability matrix, multiplied by the identity matrix.
    V p1;
    /// The probability matrix, transposes, multiplied by the identity matrix.
    V pt1;
    /// The probability matrix multiplied by the fixed points.
    M px;
    /// The total error.
    typename M::Scalar l;
    /// The correspondence vector between the two datasets.
    IndexVector correspondence;
};

/// Abstract base class for Gauss transforms.
template <typename M, typename V>
class GaussTransform {
public:
    /// Returns the default Gauss transform as a unique ptr.
    static std::unique_ptr<GaussTransform<M, V>> make_default();

    /// Computes the Gauss transform.
    virtual Probabilities<M, V> compute(const M& fixed, const M& moving,
                                        typename M::Scalar sigma2,
                                        typename M::Scalar outliers) const = 0;

    virtual ~GaussTransform() {}
};

/// The direct Gauss transform.
template <typename M, typename V>
class GaussTransformDirect : public GaussTransform<M, V> {
public:
    Probabilities<M, V> compute(const M& fixed, const M& moving,
                                typename M::Scalar sigma2,
                                typename M::Scalar outliers) const;
};
} // namespace cpd
