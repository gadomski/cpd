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

#include <cpd/find_P.hpp>

#include <cpd/figtree.hpp>


namespace cpd
{


double find_P(
        const arma::mat& X,
        const arma::mat& Y,
        double sigma2,
        float outliers,
        arma::vec& P1,
        arma::vec& Pt1,
        arma::mat& PX,
        bool use_fgt
        )
{
    P1.zeros();
    Pt1.zeros();
    PX.zeros();

    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    const int eval_method = use_fgt ? FIGTREE_EVAL_AUTO : FIGTREE_EVAL_DIRECT;

    arma::vec denomP(N);

    const double h = std::sqrt(2 * sigma2);
    const double ndi = (outliers * M * std::pow(2 * M_PI * sigma2, 0.5 * D)) / ((1 - outliers) * N);
    const double epsilon = 1e-2;
    arma::vec q = arma::ones<arma::vec>(M);

    arma::mat Xt = X.t();
    arma::mat Yt = Y.t();

    figtree_wrap(Yt, Xt, q, h, epsilon, denomP, eval_method);

    denomP = denomP + ndi;
    Pt1 = 1 - ndi / denomP;
    q = 1 / denomP;

    figtree_wrap(Xt, Yt, q, h, epsilon, P1, eval_method);

    for (int i = 0; i < D; ++i)
    {
        q = X.col(i) / denomP;
        arma::vec c = PX.unsafe_col(i);
        figtree_wrap(Xt, Yt, q, h, epsilon, c, eval_method);
    }

    return -arma::sum(arma::log(denomP)) + D * N * std::log(sigma2) / 2;
}


}
