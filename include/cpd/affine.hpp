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
/// Affine cpd registration.

#pragma once

#include <chrono>

#include <cpd/matrix.hpp>
#include <cpd/normalize.hpp>
#include <cpd/probabilities.hpp>

namespace cpd {

/// An affine transformation.
class Affine {
public:
    /// The result of an affine CPD run.
    struct Result {
        /// The affine transformation.
        Matrix transform;
        /// The ranslation vector.
        Vector translation;
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

    /// Initialize an affine transformation.
    void init(const Matrix&, const Matrix&) {}

    /// No modification of probabilities necessary.
    void modify_probabilities(Probabilities&) const {}

    /// Computes one iteration of the affine transform.
    Result compute(const Matrix& fixed, const Matrix& moving,
                   const Probabilities& probabilities, double sigma2) const;

    /// Denormalizes a result.
    void denormalize(const Normalization& normalization, Result& result) const;
};

/// Computes an affine transformation from the target onto the source.
Affine::Result affine(const Matrix& fixed, const Matrix& moving);
}
