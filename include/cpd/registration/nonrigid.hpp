/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
* 
* Derived from the Coherent Point Drift Matlab package
* Copyright (C) 2008-2009 Andriy Myronenko <myron@csee.ogi.edu>
* https://sites.google.com/site/myronenko/research/cpd
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

#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


class Nonrigid : public Base
{
public:

    explicit Nonrigid(
            float tol = 1e-5,
            int max_it = 150,
            float outliers = 0.1,
            bool use_fgt = false,
            float beta = 2,
            float lambda =  3
            );

    inline float get_beta() const { return m_beta; }
    inline float get_lambda() const { return m_lambda; }

    inline void set_beta(float beta) { m_beta = beta; }
    inline void set_lambda(float lambda) { m_lambda = lambda; }

    virtual ~Nonrigid() {};

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const;

    float m_beta;
    float m_lambda;
};


}
}
