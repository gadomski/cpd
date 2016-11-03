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
/// Configure cpd registration runs.

#pragma once

#include <cpd/comparer.hpp>
#include <cpd/logging.hpp>
#include <cpd/normalize.hpp>
#include <cpd/utils.hpp>
#include <cpd/vendor/spdlog/spdlog.h>

namespace cpd {

/// The default number of iterations allowed.
const size_t DEFAULT_MAX_ITERATIONS = 150;
/// Whether points should be normalized by default.
const bool DEFAULT_NORMALIZE = true;
/// The default outlier weight.
const double DEFAULT_OUTLIERS = 0.1;
/// The default tolerance.
const double DEFAULT_TOLERANCE = 1e-5;
/// The default sigma2.
const double DEFAULT_SIGMA2 = 0.0;
/// Whether correspondence vector should be computed by default.
const bool DEFAULT_CORRESPONDENCE = false;

/// Template class for running cpd registrations.
///
/// The two template arguments set the type of transform (e.g. Rigid) and the
/// type of probability computer (e.g. FgtProbabilityComputer).
template <typename Transform, typename ProbabilityComputer>
class Runner {
public:
    /// Creates a default Runner.
    Runner()
      : m_probability_computer(ProbabilityComputer())
      , m_correspondence(DEFAULT_CORRESPONDENCE)
      , m_logger(spdlog::get(LOGGER_NAME))
      , m_max_iterations(DEFAULT_MAX_ITERATIONS)
      , m_normalize(DEFAULT_NORMALIZE)
      , m_outliers(DEFAULT_OUTLIERS)
      , m_sigma2(DEFAULT_SIGMA2)
      , m_tolerance(DEFAULT_TOLERANCE)
      , m_transform(Transform()) {}

    /// Creates a runner with a pre-constructed probability computer and
    /// transform.
    Runner(Transform transform, ProbabilityComputer probability_computer)
      : m_probability_computer(probability_computer)
      , m_transform(transform)
      , m_max_iterations(DEFAULT_MAX_ITERATIONS)
      , m_normalize(DEFAULT_NORMALIZE)
      , m_outliers(DEFAULT_OUTLIERS)
      , m_sigma2(DEFAULT_SIGMA2)
      , m_tolerance(DEFAULT_TOLERANCE)
      , m_correspondence(DEFAULT_CORRESPONDENCE) {}

    /// Sets the maximum number of iterations allowed.
    Runner& max_iterations(size_t max_iterations) {
        m_max_iterations = max_iterations;
        return *this;
    }

    /// Sets whether the points should be normalized before running.
    Runner& normalize(bool normalize) {
        m_normalize = normalize;
        return *this;
    }

    /// Sets the initial sigma2.
    ///
    /// If this value is not set, it will be computed to a reasonable default.
    Runner& sigma2(double sigma2) {
        m_sigma2 = sigma2;
        return *this;
    }

    /// Sets the tolerance.
    Runner& tolerance(double tolerance) {
        m_tolerance = tolerance;
        return *this;
    }

    /// Sets the outlier weight.
    Runner& outliers(double outliers) {
        m_outliers = outliers;
        return *this;
    }

    /// Sets whether the correspondence vector is computed.
    Runner& correspondence(bool correspondence) {
        m_correspondence = correspondence;
        return *this;
    }

    /// Runs the cpd registration.
    typename Transform::Result run(const Matrix& fixed, const Matrix& moving) {
        const Matrix* fixed_ptr(&fixed);
        const Matrix* moving_ptr(&moving);
        Normalization normalization;
        if (m_normalize) {
            normalization = cpd::normalize(fixed, moving);
            fixed_ptr = &normalization.fixed;
            moving_ptr = &normalization.moving;
        }
        m_transform.init(*fixed_ptr, *moving_ptr);
        size_t iter = 0;
        double ntol = m_tolerance + 10.0;
        double l = 0.0;
        typename Transform::Result result;
        result.points = *moving_ptr;
        result.sigma2 = m_sigma2 == 0.0
                            ? default_sigma2(*fixed_ptr, *moving_ptr)
                            : m_sigma2;
        while (iter < m_max_iterations && ntol > m_tolerance &&
               result.sigma2 > 10 * std::numeric_limits<double>::epsilon()) {
            auto probabilities = m_probability_computer.compute(
                *fixed_ptr, result.points, result.sigma2, m_outliers);
            m_transform.modify_probabilities(probabilities);
            ntol = std::abs((probabilities.l - l) / probabilities.l);
            if (m_logger) {
                m_logger->info("iter={}, dL={:.8f}, sigma2={:.4f}", iter, ntol,
                               result.sigma2);
            }
            l = probabilities.l;
            result = m_transform.compute(*fixed_ptr, *moving_ptr, probabilities,
                                         result.sigma2);
            ++iter;
        }
        if (m_normalize) {
            m_transform.denormalize(normalization, result);
        }
        if (m_correspondence) {
            auto probabilities = DirectComparer().compute(fixed, result.points,
                                                          m_sigma2, m_outliers);
            result.correspondence = probabilities.correspondence;
        }
        return result;
    }

private:
    ProbabilityComputer m_probability_computer;
    bool m_correspondence;
    std::shared_ptr<spdlog::logger> m_logger;
    size_t m_max_iterations;
    bool m_normalize;
    double m_outliers;
    double m_sigma2;
    double m_tolerance;
    Transform m_transform;
};

/// Runs a registration with a default comparer.
template <typename Transform>
typename Transform::Result run(const Matrix& fixed, const Matrix& source) {
    Runner<Transform, DirectComparer> runner;
    return runner.run(fixed, source);
}
}
