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
/// Base class for comparers.

#pragma once

#include <cpd/matrix.hpp>
#include <cpd/probabilities.hpp>
#include <memory>

namespace cpd {

/// An abstract base class.
///
/// Comparers compare two data sets and produce several probability matrices
/// that describe the alignment between those two data sets.
class Comparer {
public:
    /// Creates the default comparer.
    static std::unique_ptr<Comparer> create();

    /// Creates a default comparer from the provided name.
    ///
    /// Acceptable names are "direct" and (if cpd is compiled with fgt support)
    /// "fgt").
    static std::unique_ptr<Comparer> from_name(const std::string& name);

    /// Computes the probabilities of alignment between fixed and moving.
    virtual Probabilities compute(const Matrix& fixed, const Matrix& moving,
                                  double sigma2, double outliers) const = 0;
};
}
