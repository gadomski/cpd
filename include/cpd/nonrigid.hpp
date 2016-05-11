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

/// \file nonrigid.hpp
/// \brief Nonrigid CPD registration.

#pragma once

#include <cpd/matrix.hpp>
#include <cpd/registration.hpp>

namespace cpd {

/// The result of a nonrigid CPD registration.
struct NonrigidResult {
    /// The aligned dataset.
    Matrix points;
};

/// Class-based interface for running a nonrigid registration.
class Nonrigid : public Registration<NonrigidResult> {
public:
    /// Default beta parameter.
    constexpr static const double DEFAULT_BETA = 3.0;
    /// Default lambda parameter.
    constexpr static const double DEFAULT_LAMBDA = 3.0;

    /// Creates a new nonrigid registration with default parameters.
    Nonrigid();

    /// Returns the value for beta.
    double beta() const { return m_beta; }
    /// Sets the value for beta.
    Nonrigid& set_beta(double beta) {
        m_beta = beta;
        return *this;
    }
    /// Returns the value for lambda.
    double lambda() const { return m_lambda; }
    /// Sets the value for lambda.
    Nonrigid& set_lambda(double lambda) {
        m_lambda = lambda;
        return *this;
    }

private:
    virtual NonrigidResult compute_impl(const MatrixRef source,
                                        const MatrixRef target, double sigma2);

    double m_beta;
    double m_lambda;
};

/// Runs nonrigid CPD on two data sets, using all default parameters.
NonrigidResult nonrigid(const MatrixRef source, const MatrixRef target);

/// Runs nonrigid CPD with the provided sigma2.
NonrigidResult nonrigid(const MatrixRef source, const MatrixRef target,
                        double sigma2);
}
