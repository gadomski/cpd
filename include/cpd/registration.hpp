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

/// \file registration.hpp
/// \brief Abstract base class template for CPD registrations.

#pragma once

#include <iostream>

#include <cpd/matrix.hpp>

namespace spdlog {
class logger;
}

namespace cpd {

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
    /// Default value for whether we should use the Fast Gauss Transform.
    static const bool DEFAULT_USE_FGT = true;
    /// Default error tolerance for the Fast Gauss Transform.
    constexpr static const double DEFAULT_FGT_EPSILON = 1e-4;
    /// Default Fast Gauss Transform bandwidth breakpoint.
    ///
    /// Above this point, we use IFGT — below, we use direct+tree.
    constexpr static const double DEFAULT_FGT_BREAKPOINT = 0.2;

    /// Creates a new registration with default values.
    Registration()
        : m_max_iterations(DEFAULT_MAX_ITERATIONS),
          m_tolerance(DEFAULT_TOLERANCE),
          m_outlier_weight(DEFAULT_OUTLIER_WEIGHT),
          m_use_fgt(DEFAULT_USE_FGT),
          m_fgt_epsilon(DEFAULT_FGT_EPSILON),
          m_fgt_breakpoint(DEFAULT_FGT_BREAKPOINT),
          m_logger() {}

    /// Returns this registration's logger.
    ///
    /// If there's no logger set, this registration will create an unregistered
    /// stdout logger and return that.
    std::shared_ptr<spdlog::logger> log();
    /// Sets this registration's logger.
    Registration& set_logger(std::shared_ptr<spdlog::logger> logger);

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

    /// Returns true if this registration will use the Fast Gauss Transform.
    bool use_fgt() const { return m_use_fgt; }
    /// Sets whether this registration will use the Fast Gauss Transform.
    Registration& use_fgt(bool use_fgt) {
        m_use_fgt = use_fgt;
        return *this;
    }

    /// Returns the fgt error tolerance.
    double fgt_epsilon() const { return m_fgt_epsilon; }
    /// Sets the fgt error tolerance.
    Registration& set_fgt_epsilon(double fgt_epsilon) {
        m_fgt_epsilon = fgt_epsilon;
        return *this;
    }

    /// Returns the fgt breakpoint.
    double fgt_breakpoint() const { return m_fgt_breakpoint; }
    /// Sets the fgt breakpoint.
    Registration& set_fgt_breakpoint(double fgt_breakpoint) {
        m_fgt_breakpoint = fgt_breakpoint;
        return *this;
    }

    /// Calculates the probability matrices for a given bandwidth.
    std::tuple<Vector, Vector, Matrix, double>
    calculate_probabilities(const MatrixRef source, const MatrixRef target,
                            double sigma2) const;

    /// Registers two datasets.
    T compute(const MatrixRef source, const MatrixRef target);
    /// Registers two datasets with the provided sigma2.
    T compute(const MatrixRef source, const MatrixRef target, double sigma2);

private:
    virtual T compute_impl(const MatrixRef source, const MatrixRef target,
                           double sigma2) = 0;

    size_t m_max_iterations;
    double m_tolerance;
    double m_outlier_weight;
    bool m_use_fgt;
    double m_fgt_epsilon;
    double m_fgt_breakpoint;
    std::shared_ptr<spdlog::logger> m_logger;
};
}
