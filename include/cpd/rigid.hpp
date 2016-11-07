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

/// \file
/// Rigid cpd registration.

#pragma once

#include <chrono>

#include <cpd/matrix.hpp>
#include <cpd/normalize.hpp>
#include <cpd/probabilities.hpp>

namespace cpd {

const bool DEFAULT_ALLOW_REFLECTIONS = false;
const bool DEFAULT_SCALE = false;

/// Rigid coherent point drift.
///
/// Rotation, translation, and possibly scaling.
class Rigid {
public:
    /// The result of a rigid transformation.
    struct Result {
        /// The rotation from the moving points onto the fixed points.
        Matrix rotation;
        /// The translation from the moving points onto the fixed points.
        Vector translation;
        /// The scaling factor.
        double scale;
        /// The transformed points.
        Matrix points;
        /// The final sigma2.
        double sigma2;
        /// The correspondence vector (optional).
        IndexVector correspondence;
        /// The runtime.
        std::chrono::microseconds runtime;
        /// The number of iterations until convergence.
        size_t iterations;
    };

    /// Creates a default rigid transformation.
    Rigid()
      : m_allow_reflections(DEFAULT_ALLOW_REFLECTIONS)
      , m_scale(DEFAULT_SCALE) {}

    /// No initialization necessary.
    void init(const Matrix&, const Matrix&) {}

    /// No modification of probabilities necessary.
    void modify_probabilities(Probabilities&) const {}

    /// Sets whether this rigid allows scaling or not.
    Rigid& scale(bool scale) {
        m_scale = scale;
        return *this;
    }

    /// Computes one iteration of the rigid transformation.
    Result compute(const Matrix& fixed, const Matrix& moving,
                   const Probabilities& probabilities, double sigma2) const;

    /// Denormalizes a result.
    void denormalize(const Normalization& normalization, Result& result) const;

private:
    bool m_allow_reflections;
    bool m_scale;
};

/// Computes a rigid transformation from the target onto the source.
Rigid::Result rigid(const Matrix& fixed, const Matrix& moving);

/// Prints the rigid result to an ostream.
std::ostream& operator<<(std::ostream& stream, const Rigid::Result& result);
}
