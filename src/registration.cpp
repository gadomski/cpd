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

#include <cpd/registration.hpp>

#include "debug.hpp"
#include "exceptions.hpp"
#include "find_P.hpp"
#include "sigma2.hpp"


namespace cpd {


Registration::Registration(float tol, int max_it, float outliers, bool use_fgt,
                           float epsilon, float z_exaggeration, float sigma2)
    : m_tol(tol),
      m_max_it(max_it),
      m_outliers(outliers),
      m_use_fgt(use_fgt),
      m_epsilon(epsilon),
      m_z_exaggeration(z_exaggeration),
      m_sigma2(sigma2) {}


Registration::~Registration() {}


Registration::ResultPtr Registration::run(const arma::mat& X,
                                          const arma::mat& Y) const {
    DEBUG("Running registration, X.n_rows: " << X.n_rows
                                             << ", Y.n_rows: " << Y.n_rows);
    if (X.n_cols != Y.n_cols) {
        throw cpd::dimension_mismatch(
            "X and Y do not have the same number of columns");
    }
    arma::mat Xn(X), Yn(Y);
    Normalization normal = normalize(Xn, Yn);
    double sigma2 = get_sigma2() == 0.0f ? calculate_sigma2(Xn, Yn)
                                         : get_sigma2() / normal.scale;

    DEBUG("Normalized with scale: "
          << normal.scale << ", xd: (" << normal.xd(0) << "," << normal.xd(1)
          << "," << normal.xd(2) << "), yd: (" << normal.yd(0) << ","
          << normal.yd(1) << "," << normal.yd(2) << ")"
          << ", z-exaggeration: " << get_z_exaggeration()
          << ", sigma2_init: " << sigma2);
    ResultPtr result = execute(Xn, Yn, sigma2);
    denormalize(result, normal);
    return result;
}


Registration::Normalization Registration::normalize(arma::mat& X,
                                                    arma::mat& Y) const {
    Normalization normal;

    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;

    // TODO formalize which column is which, so we don't have to implicitly
    // kno which column is Z.
    X.col(2) = X.col(2) * get_z_exaggeration();

    normal.xd = arma::mean(X);
    normal.yd = arma::mean(Y);

    X = X - arma::repmat(normal.xd, N, 1);
    Y = Y - arma::repmat(normal.yd, M, 1);

    auto scale = [](const arma::mat& mat) -> arma::uword {
        return arma::as_scalar(
            arma::max(arma::max(mat, 0) - arma::min(mat, 0), 1));
    };

    normal.scale = std::max(scale(X), scale(Y));

    X = X / normal.scale;
    Y = Y / normal.scale;

    return normal;
}


void Registration::denormalize(ResultPtr& result,
                               const Normalization& normal) const {
    result->Y = result->Y * normal.scale + arma::repmat(normal.xd, result->Y.n_rows, 1);
    result->Y.col(2) = result->Y.col(2) / get_z_exaggeration();
}


double Registration::find_P(const arma::mat& X, const arma::mat& Y,
                            double sigma2, arma::vec& P1, arma::vec& Pt1,
                            arma::mat& PX) const {
    return cpd::find_P(X, Y, sigma2, get_outliers(), P1, Pt1, PX, use_fgt(),
                       get_epsilon());
}
}
