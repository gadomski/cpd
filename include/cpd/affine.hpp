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
/// Affine (translation, rotation, skew, scaling) transformation.

#pragma once

#include <cpd/transform.hpp>

namespace cpd {

/// The result of a affine coherent point drift run.
template <typename M, typename V>
class AffineResult : public Result<M, V> {
public:
    /// The affine transformation.
    M transform;

    /// The translation vector.
    V translation;

    /// Returns the transform and the translation as one matrix.
    M matrix() const;

    /// Denormalize this result.
    void denormalize(const Normalization<M, V>& normalization);
};

/// Affine coherent point drift.
template <typename M, typename V>
class Affine : public Transform<M, V, AffineResult> {
public:
    Affine()
      : Transform<M, V, AffineResult>()
      , m_linked(DEFAULT_LINKED) {}

    /// Computes one iteration of the affine transformation.
    AffineResult<M, V> compute_one(const M& fixed, const M& moving,
                                   const Probabilities<M, V>& probabilities,
                                   typename M::Scalar sigma2) const;

    /// Sets whether the scalings of the two datasets are linked.
    Affine& linked(bool linked) {
        m_linked = linked;
        return *this;
    }

    virtual bool linked() const { return m_linked; }

private:
    bool m_linked;
};

/// Runs a affine registration on two matrices.
template <typename M, typename V>
AffineResult<M, V> affine(const M& fixed, const M& moving);
} // namespace cpd
