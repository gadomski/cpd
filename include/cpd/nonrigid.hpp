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

#include <cpd/registration.hpp>


namespace cpd {


class Nonrigid : public Registration {
public:
    explicit Nonrigid(float tol = DefaultTolerance,
                      int max_it = DefaultMaxIterations,
                      float outliers = DefaultOutliers,
                      bool use_fgt = DefaultFgt, float epsilon = DefaultEpsilon,
                      float beta = DefaultBeta, float lambda = DefaultLambda);

    inline float get_beta() const { return m_beta; }
    inline float get_lambda() const { return m_lambda; }

    inline void set_beta(float beta) { m_beta = beta; }
    inline void set_lambda(float lambda) { m_lambda = lambda; }

    virtual ~Nonrigid(){};

private:
    virtual ResultPtr execute(const arma::mat& X, const arma::mat& Y,
                              double sigma2) const;

    float m_beta;
    float m_lambda;
};
}
