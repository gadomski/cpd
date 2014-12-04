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

#include <cpd/registration/base.hpp>

#include <cpd/debug.hpp>
#include <cpd/exceptions.hpp>
#include <cpd/find_P.hpp>


namespace cpd
{
namespace registration
{


Base::Base(float tol, int max_it, float outliers, bool use_fgt, float epsilon)
    : m_tol(tol)
    , m_max_it(max_it)
    , m_outliers(outliers)
    , m_use_fgt(use_fgt)
    , m_epsilon(epsilon)
{}


SpResult Base::operator()(const arma::mat& X, const arma::mat& Y) const
{
    DEBUG("Running registration, X.n_rows: " << X.n_rows << ", Y.n_rows: " << Y.n_rows);
    if (X.n_cols != Y.n_cols)
    {
        throw cpd::dimension_mismatch("X and Y do not have the same number of columns");
    }
    arma::mat Xn(X), Yn(Y);
    Normalization normal = normalize(Xn, Yn);
    DEBUG("Normalized with scale: " << normal.scale << 
            ", xd: (" << normal.xd(0) << "," << normal.xd(1) << "," << normal.xd(2) <<
            "), yd: (" << normal.yd(0) << "," << normal.yd(1) << "," << normal.yd(2) << ")");
    SpResult result = execute(Xn, Yn);
    denormalize(result->Y, normal);
    return result;
}


Normalization Base::normalize(arma::mat& X, arma::mat& Y) const
{
    Normalization normal;

    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;

    normal.xd = arma::mean(X);
    normal.yd = arma::mean(Y);

    X = X - arma::repmat(normal.xd, N, 1);
    Y = Y - arma::repmat(normal.yd, M, 1);

    normal.scale = std::sqrt(arma::sum(arma::sum(arma::pow(Y, 2), 2)) / M);

    X = X / normal.scale;
    Y = Y / normal.scale;

    return normal;
}


void Base::denormalize(arma::mat& Y, const Normalization& normal) const
{
    Y = Y * normal.scale + arma::repmat(normal.xd, Y.n_rows, 1);
}


double Base::find_P(
        const arma::mat& X,
        const arma::mat& Y,
        double sigma2,
        arma::vec& P1,
        arma::vec& Pt1,
        arma::mat& PX
        ) const
{
    return cpd::find_P(X, Y, sigma2, get_outliers(), P1, Pt1, PX, use_fgt(), get_epsilon());
}


}
}
