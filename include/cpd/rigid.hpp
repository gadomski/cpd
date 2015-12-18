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


class Rigid : public Registration {
public:
    explicit Rigid(float tol = DefaultTolerance,
                   int max_it = DefaultMaxIterations,
                   float outliers = DefaultOutliers, bool use_fgt = DefaultFgt,
                   float epsilon = DefaultEpsilon,
                   bool strict_rot = DefaultStrictRotation,
                   bool use_scaling = DefaultUseScaling);

    bool strict_rot() const { return m_strict_rot; }
    bool use_scaling() const { return m_use_scaling; }
    void denormalize(ResultPtr& Y, const Normalization& normal) const override;

    void strict_rot(bool strict_rot) { m_strict_rot = strict_rot; }
    void use_scaling(bool use_scaling) { m_use_scaling = use_scaling; }

    virtual ~Rigid();

private:
    virtual ResultPtr execute(const arma::mat& X, const arma::mat& Y,
                              double sigma2) const override;

    bool m_strict_rot;
    bool m_use_scaling;
};
}
