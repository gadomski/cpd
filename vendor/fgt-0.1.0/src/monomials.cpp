// fgt, C++ library for Fast Gauss Transforms
// Copyright (C) 2015 Peter J. Gadomski <pete.gadomski@gmail.com>
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

#include "monomials.hpp"

#include "p_max_total.hpp"


namespace fgt {


void compute_monomials(const arma::rowvec& dx, arma::uword p_max,
                       std::vector<double>& monomials) {
    arma::vec heads = arma::zeros<arma::vec>(dx.n_cols);
    monomials[0] = 1;

    for (arma::uword k = 1, t = 1, tail = 1; k < p_max; ++k, tail = t) {
        for (arma::uword i = 0; i < dx.n_cols; ++i) {
            arma::uword head = heads[i];
            heads[i] = t;
            for (arma::uword j = head; j < tail; ++j, ++t) {
                monomials[t] = dx[i] * monomials[j];
            }
        }
    }
}
}
