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

#include <armadillo>

#include <cpd/defaults.hpp>
#include <cpd/registration/normalization.hpp>
#include <cpd/registration/result.hpp>


namespace cpd
{
namespace registration
{


class Base
{
public:

    explicit Base(
            // Tolerance criterium
            float tol = DEFAULT_TOLERANCE,

            // Maximum number of iterations allowed
            int max_it = DEFAULT_MAX_ITERATIONS,

            // The weight of noise and outliers
            float outliers = DEFAULT_OUTLIERS,

            // Use a Fast Gauss Transform (less accurate but faster)
            bool use_fgt = DEFAULT_FGT,

            // Tolerance level for the Fast Gauss Transform
            float epsilon = DEFAULT_EPSILON
            );

    SpResult operator()(const arma::mat& X, const arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(arma::mat& Y, const Normalization& normal) const;

    double find_P(
            const arma::mat& X,
            const arma::mat& Y,
            double sigma2,
            arma::vec& P1,
            arma::vec& Pt1,
            arma::mat& PX
            ) const;

    inline float get_tol() const { return m_tol; }
    inline int get_max_it() const { return m_max_it; }
    inline float get_outliers() const { return m_outliers; }
    inline bool use_fgt() const { return m_use_fgt; }
    inline float get_epsilon() const { return m_epsilon; }

    inline void set_tol(float tol) { m_tol = tol; }
    inline void set_max_it(int max_it) { m_max_it = max_it; }
    inline void set_outliers(float outliers) { m_outliers = outliers; }
    inline void use_fgt(bool use_fgt) { m_use_fgt = use_fgt; }
    inline void set_epsilon(float epsilon) { m_epsilon = epsilon; }

    virtual ~Base() {};

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const = 0;

    float m_tol;
    int m_max_it;
    float m_outliers;
    bool m_use_fgt;
    float m_epsilon;

};


}
}
