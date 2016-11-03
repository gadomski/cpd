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
/// Compute correpondence proabilities between two datasets.

#pragma once

#include <fgt.hpp>

#include <cpd/matrix.hpp>

namespace cpd {

const double DEFAULT_EPSILON = 1e-4;

/// Probabilities of correspondence between two datasets.
struct Probabilities {
    Vector p1;
    Vector pt1;
    Matrix px;
    double l;
    /// Corrsepondence vector between the two datasets.
    ///
    /// Only produced by the DirectProbabilityComputer.
    IndexVector correspondence;
};

/// Use Myronenko's slow direct method to calculate probabilities.
class DirectProbabilityComputer {
public:
    Probabilities compute(const Matrix& fixed, const Matrix& moving,
                          double sigma2, double outliers) const;
};

/// Use the fgt library to calculate probabilities.
class FgtProbabilityComputer {
public:
    FgtProbabilityComputer()
      : m_epsilon(DEFAULT_EPSILON) {}

    /// Computes the probabilities using the fgt library.
    Probabilities compute(const Matrix& fixed, const Matrix& moving,
                          double sigma2, double outliers) const;

private:
    std::unique_ptr<fgt::Transform> create_transform(const Matrix& points,
                                                     double bandwidth) const;

    double m_epsilon;
};
}
