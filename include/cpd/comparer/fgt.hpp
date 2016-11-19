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
/// Compute correpondence proabilities using libfgt.

#pragma once

#include <cpd/probabilities.hpp>
#include <fgt.hpp>

namespace cpd {

/// Choosing an fgt method.
enum class FgtMethod {
    /// Use the direct tree method
    ///
    /// This is the standard transform but with simplification via clustering.
    DirectTree,
    /// Use the improved fast gauss transform.
    ///
    /// This method does clustering simplifications and a series expansion to
    /// reduce the computational complexity, but works poorly with few points or
    /// small bandwidths.
    Ifgt,
    /// Switch between DirectTree and Ifgt at a breakpoint.
    Switched,
};

/// Default error tolerance for fgt.
const double DEFAULT_EPSILON = 1e-4;
/// Default Fgt method.
const FgtMethod DEFAULT_METHOD = FgtMethod::DirectTree;
/// Default ifgt->direct-tree breakpoint for fgt.
const double DEFAULT_BREAKPOINT = 0.2;

/// Use the fgt library to calculate probabilities.
class FgtComparer {
public:
    FgtComparer()
      : m_breakpoint(DEFAULT_BREAKPOINT)
      , m_epsilon(DEFAULT_EPSILON)
      , m_method(DEFAULT_METHOD) {}

    /// Sets the ifgt->direct-tree breakpoint.
    FgtComparer& breakpoint(double breakpoint) {
        m_breakpoint = breakpoint;
        return *this;
    }

    /// Sets the epsilon.
    FgtComparer& epsilon(double epsilon) {
        m_epsilon = epsilon;
        return *this;
    }

    /// Sets the method.
    FgtComparer& method(FgtMethod method) {
        m_method = method;
        return *this;
    }

    /// Computes the probabilities using the fgt library.
    Probabilities compute(const Matrix& fixed, const Matrix& moving,
                          double sigma2, double outliers) const;

private:
    std::unique_ptr<fgt::Transform> create_transform(const Matrix& points,
                                                     double bandwidth) const;

    double m_breakpoint;
    double m_epsilon;
    FgtMethod m_method;
};
}
