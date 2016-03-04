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

#include <cpd/matrix.hpp>
#include <cpd/registration.hpp>

namespace cpd {

/// The result of a rigid CPD registration.
struct RigidResult {
    /// The aligned dataset.
    Matrix points;
    /// The calculated rotation matrix.
    Matrix rotation;
    /// The calculated translation vector.
    RowVector translation;
};

/// Class-based interface for running a rigid registration.
class Rigid : public Registration<RigidResult> {
public:
    /// Default value for `no_reflections`.
    static const bool DEFAULT_NO_REFLECTIONS = true;
    /// Default value for `allow_scaling`.
    static const bool DEFAULT_ALLOW_SCALING = false;

    /// Creates a new rigid registration with default parameters.
    Rigid();

    /// Returns true if this registration guards against reflections.
    bool no_reflections() const { return m_no_reflections; }
    /// Enables or disables reflections.
    Rigid& no_reflections(bool no_reflections) {
        m_no_reflections = no_reflections;
        return *this;
    }
    /// Returns true if this registration allows scaling of the data.
    bool allow_scaling() const { return m_allow_scaling; }
    /// Enables or disables scaling.
    Rigid& allow_scaling(bool allow_scaling) {
        m_allow_scaling = allow_scaling;
        return *this;
    }

private:
    virtual RigidResult compute_impl(const MatrixRef source,
                                     const MatrixRef target,
                                     double sigma2) const;

    bool m_no_reflections;
    bool m_allow_scaling;
};

/// Runs rigid CPD on two data sets, using all default parameters.
RigidResult rigid(const MatrixRef source, const MatrixRef target);

/// Runs rigid CPD with the provided sigma2.
RigidResult rigid(const MatrixRef source, const MatrixRef target,
                  double sigma2);
}
