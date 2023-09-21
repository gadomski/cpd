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
/// Nonrigid coherent point drift transform.

#pragma once

#include <cpd/transform.hpp>

namespace cpd {

/// Default value for beta.
const Matrix::Scalar DEFAULT_BETA = 3.0;
/// Default value for lambda.
const Matrix::Scalar DEFAULT_LAMBDA = 3.0;

/// The result of a nonrigid coherent point drift run.
template <typename M, typename V>
class NonrigidResult : public Result<M, V> {};

/// Nonrigid coherent point drift.
template <typename M, typename V>
class Nonrigid : public Transform<M, V, NonrigidResult> {
public:
    Nonrigid()
      : Transform<M, V, NonrigidResult>()
      , m_lambda(DEFAULT_LAMBDA)
      , m_beta(DEFAULT_BETA)
      , m_linked(DEFAULT_LINKED) {}

    /// Initialize this transform for the provided matrices.
    void init(const M& fixed, const M& moving);

    /// Modifies the probabilities with some affinity and weight information.
    void modify_probabilities(Probabilities<M, V>& probabilities) const;

    /// Sets the beta.
    Nonrigid<M, V>& beta(double beta) {
        m_beta = beta;
        return *this;
    }

    /// Sets the lambda.
    Nonrigid<M, V>& lambda(double lambda) {
        m_lambda = lambda;
        return *this;
    }

    /// Computes one iteration of the nonrigid transformation.
    NonrigidResult<M, V> compute_one(const M& fixed, const M& moving,
                                     const Probabilities<M, V>& probabilities,
                                     typename M::Scalar sigma2) const;

    /// Sets whether the scalings of the two datasets are linked.
    Nonrigid<M, V>& linked(bool linked) {
        m_linked = linked;
        return *this;
    }

    virtual bool linked() const { return m_linked; }

private:
    M m_g;
    M m_w;
    double m_lambda;
    double m_beta;
    bool m_linked;
};

/// Runs a nonrigid registration on two matrices.
template <typename M, typename V>
NonrigidResult<M, V> nonrigid(const M& fixed, const M& moving);
} // namespace cpd
