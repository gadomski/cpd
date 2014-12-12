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

#include <cpd/registration/rigid.hpp>

#include "debug.hpp"
#include "sigma2.hpp"


namespace cpd
{
namespace registration
{


Rigid::Rigid(float tol, int max_it, float outliers, bool use_fgt, float epsilon,
             bool strict_rot, bool use_scaling)
    : Base(tol, max_it, outliers, use_fgt, epsilon)
    , m_strict_rot(strict_rot)
    , m_use_scaling(use_scaling)
{}


SpResult Rigid::execute(const arma::mat& X, const arma::mat& Y) const
{
    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    double sigma2 = get_sigma2(X, Y);
    const double sigma2_init = sigma2;

    arma::mat T = Y;
    double s = 1;
    arma::mat R = arma::eye<arma::mat>(D, D);

    int iter = 0;
    double ntol = get_tol() + 10;
    double L = 0;

    double L_old, Np;
    arma::vec P1(M), Pt1(M), mu_x(D), mu_y(D), t(D);
    arma::mat PX(M, D), A(D, D);

    while (iter < get_max_it() &&
           ntol > get_tol() &&
           sigma2 > 10 * std::numeric_limits<double>::epsilon())
    {
        L_old = L;
        L = find_P(X, T, sigma2, P1, Pt1, PX);

        ntol = std::abs((L - L_old) / L);

        DEBUG("rigid iteration: dL= " << ntol << ", iter= " << iter <<
              ", sigma2= " << sigma2);

        Np = arma::sum(Pt1);
        mu_x = X.t() * Pt1 / Np;
        mu_y = Y.t() * P1 / Np;

        A = PX.t() * Y - Np * (mu_x * mu_y.t());

        arma::mat U(D, D), V(D, D);
        arma::mat C = arma::eye<arma::mat>(D, D);
        arma::vec sv;
        arma::svd(U, sv, V, A);
        arma::mat S = arma::diagmat(sv);

        if (strict_rot())
        {
            C(D - 1, D - 1) = arma::det(U * V.t());
        }

        R = U * C * V.t();

        if (use_scaling())
        {
            s = arma::trace(S * C) /
                (arma::accu(arma::pow(Y, 2) % arma::repmat(P1, 1, D)) -
                 Np * arma::as_scalar(mu_y.t() * mu_y));
            sigma2 = std::abs(
                         arma::accu(arma::pow(Y, 2) % arma::repmat(Pt1, 1, D)) -
                         Np * arma::as_scalar(mu_x.t() * mu_x) -
                         s * arma::trace(S * C)) /
                     (Np * D);
        }
        else
        {
            sigma2 = std::abs((
                                  arma::accu(arma::pow(X, 2) % arma::repmat(Pt1, 1, D)) -
                                  Np * arma::as_scalar(mu_x.t() * mu_x) -
                                  arma::accu(arma::pow(Y, 2) % arma::repmat(P1, 1, D)) -
                                  Np * arma::as_scalar(mu_y.t() * mu_y) -
                                  2 * arma::trace(S * C)) /
                              (Np * D));
        }

        t = mu_x - s * R * mu_y;
        T = s * Y * R.t() + arma::repmat(t.t(), M, 1);

        iter++;
    }

    SpResult result(new Result());
    result->Y = T;
    return result;
}


}
}
