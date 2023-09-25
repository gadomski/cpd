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
/// Rigid coherent point drift.

#pragma once

#include <cpd/transform.hpp>

namespace cpd {

/// Should rigid registrations allow reflections by default?
const bool DEFAULT_REFLECTIONS = false;
/// Should rigid registrations scale the data by default?
const bool DEFAULT_SCALE = !DEFAULT_LINKED;

/// The result of a rigid coherent point drift run.
template <typename M, typename V>
struct RigidResult : public Result<M, V> {
    /// The rotation component of the transformation.
    M rotation;
    /// The translation component of the transformation.
    V translation;
    /// The scaling component of the transformation.
    double scale;

    /// Returns a single matrix that contains all the transformation
    /// information.
    M matrix() const;

    void denormalize(const Normalization<M, V>& normalization);
};

/// Rigid coherent point drift.
///
/// Scaling and reflections can be turned on and off.
template <typename M, typename V>
class Rigid : public Transform<M, V, RigidResult> {
public:
    Rigid()
      : Transform<M, V, RigidResult>()
      , m_reflections(DEFAULT_REFLECTIONS)
      , m_scale(DEFAULT_SCALE) {}

    /// Sets whether this rigid transform allows reflections.
    Rigid& reflections(bool reflections) {
        m_reflections = reflections;
        return *this;
    }

    /// Sets whether this rigid transform allows scaling.
    Rigid& scale(bool scale) {
        m_scale = scale;
        return *this;
    }

    /// Computes one iteration of the rigid transformation.
    RigidResult<M, V> compute_one(const M& fixed, const M& moving,
                                  const Probabilities<M, V>& probabilities,
                                  typename M::Scalar sigma2) const;

    virtual bool linked() const { return !m_scale; }

private:
    bool m_reflections;
    bool m_scale;
};

/// Runs a rigid registration on two matrices.
template <typename M, typename V>
RigidResult<M, V> rigid(const M& fixed, const M& moving);
} // namespace cpd
