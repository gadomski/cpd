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

#pragma once

#include <iostream>

#include <cpd/matrix.hpp>
#include <cpd/normalization.hpp>

namespace cpd {

/// Returns the default sigma2 value for these two datasets.
///
/// This is a default value that is based upton the variance of those datasets.
double default_sigma2(const MatrixRef source, const MatrixRef target);

/// Class template that makes it easier to create new registrations.
template <typename T>
class Registration {
public:
    /// Default maximum number of iterations.
    static const size_t DEFAULT_MAX_ITERATIONS = 150;
    /// Default error tolerance.
    constexpr static const double DEFAULT_TOLERANCE = 1e-5;
    /// Default outlier weight.
    constexpr static const double DEFAULT_OUTLIER_WEIGHT = 0.1;

    /// Creates a new registration with default values.
    Registration()
        : m_max_iterations(DEFAULT_MAX_ITERATIONS),
          m_tolerance(DEFAULT_TOLERANCE),
          m_outlier_weight(DEFAULT_OUTLIER_WEIGHT),
          m_ostream(std::cout) {}

    /// Returns an ostream that can be used to print messages.
    ///
    /// Defaults to std::cout.
    std::ostream& log() const { return m_ostream; }

    /// Returns the maximum number of iterations allowed.
    size_t max_iterations() const { return m_max_iterations; }
    /// Sets the maximum number of iterations.
    Registration& set_max_iterations(size_t max_iterations) {
        m_max_iterations = max_iterations;
        return *this;
    }
    /// Returns the error tolerance.
    double tolerance() const { return m_tolerance; }
    /// Sets the error tolerance.
    Registration& set_tolerance(double tolerance) {
        m_tolerance = tolerance;
        return *this;
    }
    /// Returns the weight given to outliers.
    double outlier_weight() const { return m_outlier_weight; }
    /// Sets the outlier weight.
    Registration& set_outlier_weight(double outlier_weight) {
        m_outlier_weight = outlier_weight;
        return *this;
    }

    /// Registers two datasets.
    T compute(const MatrixRef source, const MatrixRef target) const {
        double sigma2 = default_sigma2(source, target);
        return compute(source, target, sigma2);
    }

    /// Registers two datasets with the provided sigma2.
    T compute(const MatrixRef source, const MatrixRef target,
              double sigma2) const {
        Normalization normalization(source, target, sigma2);
        T result = compute_impl(normalization.source(), normalization.target(),
                                normalization.sigma2());
        return normalization.denormalize(result);
    }

private:
    virtual T compute_impl(const MatrixRef source, const MatrixRef target,
                           double sigma2) const = 0;

    size_t m_max_iterations;
    double m_tolerance;
    double m_outlier_weight;
    std::ostream& m_ostream;
};
}
