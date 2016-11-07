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
/// Nonrigid cpd registration.

#pragma once

#include <chrono>

#include <cpd/matrix.hpp>
#include <cpd/normalize.hpp>
#include <cpd/probabilities.hpp>

namespace cpd {

/// Default value for beta.
const double DEFAULT_BETA = 3.0;
/// Default value for lambda.
const double DEFAULT_LAMBDA = 3.0;

/// A nonrigid registration.
class Nonrigid {
public:
    /// The result of a nonrigid transformation.
    struct Result {
        /// The resultant points.
        Matrix points;
        /// The last sigma2.
        double sigma2;
        /// The correspondence vector (optional).
        IndexVector correspondence;
        /// The runtime.
        std::chrono::microseconds runtime;
    };

    /// Creates a default nonrigid registration.
    Nonrigid()
      : m_beta(DEFAULT_BETA)
      , m_lambda(DEFAULT_LAMBDA)
      , m_g()
      , m_w() {}

    /// Initializes the nonrigid transformation.
    void init(const Matrix& fixed, const Matrix& moving);

    /// Modifies the probabilities after calculation.
    void modify_probabilities(Probabilities& probabilities) const;

    /// Computes one iteration of the nonrigid transformation.
    Result compute(const Matrix& fixed, const Matrix& moving,
                   const Probabilities& probabilities, double sigma2);

    /// Denormalizes a result.
    void denormalize(const Normalization& normalization, Result& result) const;

private:
    double m_beta;
    double m_lambda;
    Matrix m_g;
    Matrix m_w;
};

/// Runs nonrigid registration using sensible defaults.
Nonrigid::Result nonrigid(const Matrix& fixed, const Matrix& moving);
}
