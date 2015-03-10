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

#include <armadillo>

#include <figtree.h>


namespace cpd {


// Assume that the input matrices have already been tranposed so
// callers can re-use transposed matrices.
inline void figtree_wrap(arma::mat& Xt, arma::mat& Yt, arma::vec& q, double h,
                         float epsilon, arma::vec& out,
                         int eval_method = FIGTREE_EVAL_AUTO) {
    const arma::uword N = Xt.n_cols;
    const arma::uword M = Yt.n_cols;
    const arma::uword D = Yt.n_rows;
    const int W = 1;

    figtree(D, N, M, W, Xt.memptr(), h, q.memptr(), Yt.memptr(), epsilon,
            out.memptr(), eval_method);
}
}
