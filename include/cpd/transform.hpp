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
/// Generic coherent point drift transform.
///
/// Downstreams shouldn't need to include this file directly, use a realization
/// of a transform (e.g. `Rigid`) instead.

#pragma once

#include <chrono>
#include <cpd/gauss_transform.hpp>
#include <cpd/matrix.hpp>
#include <cpd/normalization.hpp>
#include <cpd/utils.hpp>
#include <memory>

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
/// Are the scalings of the two datasets linked by default?
const bool DEFAULT_LINKED = true;

/// The result of a generic transform run.
struct Result {
    /// The final moved points.
    Matrix points;
    /// The final sigma2 value.
    double sigma2;
    /// The correspondence vector.
    IndexVector correspondence;
    /// The runtime.
    std::chrono::microseconds runtime;
    /// The number of iterations.
    size_t iterations;

    /// De-normalize this result.
    ///
    /// Generally, this scales the points back, and sometimes adjust transforms
    /// or shifts or the like.
    virtual void denormalize(const Normalization& normalization);
};

/// Generic coherent point drift transform.
///
/// An abstract base class for real transforms, e.g. `Rigid` or `Nonrigid`.
template <typename Result>
class Transform {
public:
    Transform()
      : m_correspondence(DEFAULT_CORRESPONDENCE)
      , m_gauss_transform(GaussTransform::make_default())
      , m_max_iterations(DEFAULT_MAX_ITERATIONS)
      , m_normalize(DEFAULT_NORMALIZE)
      , m_outliers(DEFAULT_OUTLIERS)
      , m_sigma2(DEFAULT_SIGMA2)
      , m_tolerance(DEFAULT_TOLERANCE) {}

    /// Sets whether the correspondence vector will be computed.
    Transform& correspondence(bool correspondence) {
        m_correspondence = correspondence;
        return *this;
    }

    /// Sets the gauss transform.
    Transform& gauss_transform(
        std::unique_ptr<GaussTransform> gauss_transform) {
        m_gauss_transform = std::move(gauss_transform);
        return *this;
    }

    /// Sets the max iterations for this transform.
    Transform& max_iterations(double max_iterations) {
        m_max_iterations = max_iterations;
        return *this;
    }

    /// Sets whether to normalize the points before running cpd.
    Transform& normalize(bool normalize) {
        m_normalize = normalize;
        return *this;
    }

    /// Sets the outlier tolerance.
    Transform& outliers(double outliers) {
        m_outliers = outliers;
        return *this;
    }

    /// Sets the sigma2 value for this transform.
    Transform& sigma2(double sigma2) {
        m_sigma2 = sigma2;
        return *this;
    }

    /// Sets the final tolerance.
    Transform& tolerance(double tolerance) {
        m_tolerance = tolerance;
        return *this;
    }

    /// Runs this transform for the provided matrices.
    Result run(Matrix fixed, Matrix moving) {
        auto tic = std::chrono::high_resolution_clock::now();
        Normalization normalization(fixed, moving, linked());
        if (m_normalize) {
            fixed = normalization.fixed;
            moving = normalization.moving;
        }

        this->init(fixed, moving);

        Result result;
        result.points = moving;
        if (m_sigma2 == 0.0) {
            result.sigma2 = cpd::default_sigma2(fixed, moving);
        } else if (m_normalize) {
            result.sigma2 = m_sigma2 / normalization.fixed_scale;
        } else {
            result.sigma2 = m_sigma2;
        }

        size_t iter = 0;
        double ntol = m_tolerance + 10.0;
        double l = 0.;
        while (iter < m_max_iterations && ntol > m_tolerance &&
               result.sigma2 > 10 * std::numeric_limits<double>::epsilon()) {
            Probabilities probabilities = m_gauss_transform->compute(
                fixed, result.points, result.sigma2, m_outliers);
            this->modify_probabilities(probabilities);

            ntol = std::abs((probabilities.l - l) / probabilities.l);
            l = probabilities.l;

            result =
                this->compute_one(fixed, moving, probabilities, result.sigma2);
            ++iter;
        }

        if (m_normalize) {
            result.denormalize(normalization);
        }
        if (m_correspondence) {
            Probabilities probabilities = m_gauss_transform->compute(
                fixed, result.points, m_sigma2, m_outliers);
            result.correspondence = probabilities.correspondence;
            assert(result.correspondence.rows() > 0);
        }
        auto toc = std::chrono::high_resolution_clock::now();
        result.runtime =
            std::chrono::duration_cast<std::chrono::microseconds>(toc - tic);
        result.iterations = iter;
        return result;
    }

    /// Initialize this transform for the provided matrices.
    ///
    /// This is called before beginning each run, but after normalization. In
    /// general, transforms shouldn't need to be initialized, but the nonrigid
    /// does.
    virtual void init(const Matrix& fixed, const Matrix& moving) {}

    /// Modifies `Probabilities` in some way.
    ///
    /// Some types of transform need to tweak the probabilities before moving on
    /// with an interation. The default behavior is to do nothing.
    virtual void modify_probabilities(Probabilities& probabilities) const {}

    /// Computes one iteration of the transform.
    virtual Result compute_one(const Matrix& fixed, const Matrix& moving,
                               const Probabilities& probabilities,
                               double sigma2) const = 0;

    /// Returns true if the normalization should be linked.
    ///
    /// No effect if no normalization is applied.
    virtual bool linked() const = 0;

private:
    bool m_correspondence;
    std::unique_ptr<GaussTransform> m_gauss_transform;
    size_t m_max_iterations;
    bool m_normalize;
    double m_outliers;
    double m_sigma2;
    double m_tolerance;
};
} // namespace cpd
