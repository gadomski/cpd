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

#include "find_P.hpp"

#include <fgt/fgt.hpp>


namespace cpd {


double find_P(const arma::mat& X, const arma::mat& Y, double sigma2,
              float outliers, arma::vec& P1, arma::vec& Pt1, arma::mat& PX,
              bool use_fgt, const float epsilon) {
    P1.zeros();
    Pt1.zeros();
    PX.zeros();

    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    const double h = std::sqrt(2 * sigma2);
    const double ndi = (outliers * M * std::pow(2 * M_PI * sigma2, 0.5 * D)) /
                       ((1 - outliers) * N);
    arma::vec q = arma::ones<arma::vec>(M);

    fgt::GaussTransformUnqPtr transformY;
    if (use_fgt) {
        transformY = fgt::choose_gauss_transform(Y, h, epsilon);
    } else {
        transformY.reset(new fgt::Direct(Y, h));
    }
    arma::vec denomP = transformY->compute(X, q);

    denomP = denomP + ndi;
    Pt1 = 1 - ndi / denomP;
    q = 1 / denomP;

    fgt::GaussTransformUnqPtr transformX;
    if (use_fgt) {
        transformX = fgt::choose_gauss_transform(X, h, epsilon);
    } else {
        transformX.reset(new fgt::Direct(X, h));
    }
    P1 = transformX->compute(Y, q);

    for (int i = 0; i < D; ++i) {
        q = X.col(i) / denomP;
        arma::vec c = PX.unsafe_col(i);
        PX.col(i) = transformX->compute(Y, q);
    }

    return -arma::sum(arma::log(denomP)) + D * N * std::log(sigma2) / 2;
}
}
