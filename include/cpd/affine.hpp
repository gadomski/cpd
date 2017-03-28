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
struct AffineResult : public Result {
    /// The affine transformation.
    Matrix transform;

    /// The translation vector.
    Vector translation;

    /// Returns the transform and the translation as one matrix.
    Matrix matrix() const;

    /// Denormalize this result.
    void denormalize(const Normalization& normalization);
};

/// Affine coherent point drift.
class Affine : public Transform<AffineResult> {
public:
    Affine()
      : Transform()
      , m_linked(DEFAULT_LINKED) {}

    /// Computes one iteration of the affine transformation.
    AffineResult compute_one(const Matrix& fixed, const Matrix& moving,
                             const Probabilities& probabilities,
                             double sigma2) const;

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
AffineResult affine(const Matrix& fixed, const Matrix& moving);
} // namespace cpd
