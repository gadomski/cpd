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

#include <cpd/nonrigid.hpp>


namespace cpd {


class NonrigidLowrank : public Nonrigid {
public:
    explicit NonrigidLowrank(
        float tol = DefaultTolerance, int max_it = DefaultMaxIterations,
        float outliers = DefaultOutliers, bool use_fgt = DefaultFgt,
        float epsilon = DefaultEpsilon, float beta = DefaultBeta,
        float lambda = DefaultLambda,
        // Andriy's Matlab implementation recommends setting this to
        // M ^ (1/2), where M is the number of points in Y
        arma::uword numeig = DefaultNumeig);

    inline arma::uword get_numeig() const { return m_numeig; }

    inline void set_numeig(int numeig) { m_numeig = numeig; }

    virtual ~NonrigidLowrank(){};

private:
    virtual ResultPtr execute(const arma::mat& X, const arma::mat& Y,
                              double sigma2) const;

    arma::uword m_numeig;
};
}
