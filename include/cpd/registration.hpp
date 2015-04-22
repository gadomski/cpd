/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#pragma once

#include <memory>

#include <armadillo>

#include <cpd/defaults.hpp>


namespace cpd {


class Registration {
public:
    struct Normalization {
        double scale;
        arma::mat xd, yd;
    };

    struct Result {
        arma::mat Y;
        arma::mat transformation;
    };

    typedef std::shared_ptr<Result> ResultPtr;

    explicit Registration(
        // Tolerance criterium
        float tol = DefaultTolerance,

        // Maximum number of iterations allowed
        int max_it = DefaultMaxIterations,

        // The weight of noise and outliers
        float outliers = DefaultOutliers,

        // Use a Fast Gauss Transform (less accurate but faster)
        bool use_fgt = DefaultFgt,

        // Tolerance level for the Fast Gauss Transform
        float epsilon = DefaultEpsilon,

        // Factor by which to exaggerate the z values
        float z_exaggeration = DefaultZExaggeration,

        // Initial sigma2 value, if zero determine auto-magically
        float sigma2 = DefaultSigma2);

    ResultPtr run(const arma::mat& X, const arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(arma::mat& Y, const Normalization& normal) const;

    double find_P(const arma::mat& X, const arma::mat& Y, double sigma2,
                  arma::vec& P1, arma::vec& Pt1, arma::mat& PX) const;

    float get_tol() const { return m_tol; }
    int get_max_it() const { return m_max_it; }
    float get_outliers() const { return m_outliers; }
    bool use_fgt() const { return m_use_fgt; }
    float get_epsilon() const { return m_epsilon; }
    float get_z_exaggeration() const { return m_z_exaggeration; }
    float get_sigma2() const { return m_sigma2; }

    void set_tol(float tol) { m_tol = tol; }
    void set_max_it(int max_it) { m_max_it = max_it; }
    void set_outliers(float outliers) { m_outliers = outliers; }
    void use_fgt(bool use_fgt) { m_use_fgt = use_fgt; }
    void set_epsilon(float epsilon) { m_epsilon = epsilon; }
    void set_z_exaggeration(float z_exaggeration) {
        m_z_exaggeration = z_exaggeration;
    }
    void set_sigma2(float sigma2) { m_sigma2 = sigma2; }

    virtual ~Registration();

private:
    virtual ResultPtr execute(const arma::mat& X, const arma::mat& Y,
                              double sigma2) const = 0;

    float m_tol;
    int m_max_it;
    float m_outliers;
    bool m_use_fgt;
    float m_epsilon;
    float m_z_exaggeration;
    float m_sigma2;
};
}
