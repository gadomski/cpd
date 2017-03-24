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
struct Probabilities {
    /// The probability matrix, multiplied by the identity matrix.
    Vector p1;
    /// The probability matrix, transposes, multiplied by the identity matrix.
    Vector pt1;
    /// The probability matrix multiplied by the fixed points.
    Matrix px;
    /// The total error.
    double l;
    /// The correspondence vector between the two datasets.
    IndexVector correspondence;
};

/// Abstract base class for Gauss transforms.
class GaussTransform {
public:
    /// Returns the default Gauss transform as a unique ptr.
    static std::unique_ptr<GaussTransform> make_default();

    /// Computes the Gauss transform.
    virtual Probabilities compute(const Matrix& fixed, const Matrix& moving,
                                  double sigma2, double outliers) const = 0;
};

/// The direct Gauss transform.
class GaussTransformDirect : public GaussTransform {
public:
    Probabilities compute(const Matrix& fixed, const Matrix& moving,
                          double sigma2, double outliers) const;
};
} // namespace cpd
