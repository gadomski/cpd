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
/// Gauss transforms using the [fgt](https://github.com/gadomski/fgt) library.

#pragma once

#include <cpd/gauss_transform.hpp>
#include <fgt.hpp>

namespace cpd {

/// The method(s) by which the fgt Gauss transform will compute the differences.
enum FgtMethod {
    /// Use only the direct-tree fgt method.
    DirectTree,
    /// Use only the improved fast Gauss transform method.
    Ifgt,
    /// Switch between direct-tree and ifgt at a certain breakpoint.
    Switched,
};

/// The default fgt method
const FgtMethod DEFAULT_FGT_METHOD = FgtMethod::DirectTree;
/// The default switched fgt breakpoint.
const typename M::Scalar DEFAULT_BREAKPOINT = 0.2;
/// The default fgt epsilon.
const typename M::Scalar DEFAULT_EPSILON = 1e-4;

/// The Gauss transform using the fgt library.
template <typename M, typename V>
class GaussTransformFgt : public GaussTransform<M, V> {
public:
    GaussTransformFgt()
      : GaussTransform()
      , m_breakpoint(DEFAULT_BREAKPOINT)
      , m_epsilon(DEFAULT_EPSILON)
      , m_method(DEFAULT_FGT_METHOD) {}

    /// Sets the ifgt->direct-tree breakpoint.
    GaussTransformFgt& breakpoint(typename M::Scalar breakpoint) {
        m_breakpoint = breakpoint;
        return *this;
    }

    /// Sets the epsilon.
    GaussTransformFgt& epsilon(typename M::Scalar epsilon) {
        m_epsilon = epsilon;
        return *this;
    }

    /// Sets the method.
    GaussTransformFgt& method(FgtMethod method) {
        m_method = method;
        return *this;
    }

    Probabilities compute(const M& fixed, const M& moving,
                          typename M::Scalar sigma2,
                          typename M::Scalar outliers) const;

private:
    std::unique_ptr<fgt::Transform> create_transform(
        const M& points, typename M::Scalar bandwidth) const;

    typename M::Scalar m_breakpoint;
    typename M::Scalar m_epsilon;
    FgtMethod m_method;
};
} // namespace cpd
