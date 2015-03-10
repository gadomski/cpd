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

#include "constant_series.hpp"

#include "p_max_total.hpp"


namespace fgt {


void compute_constant_series(arma::uword d, arma::uword p_max,
                             std::vector<double>& series) {
    arma::uvec heads = arma::zeros<arma::uvec>(d + 1);
    heads(d) = std::numeric_limits<arma::uword>::max();
    arma::uvec cinds = arma::zeros<arma::uvec>(series.size());
    series[0] = 1;

    for (arma::uword k = 1, t = 1, tail = 1; k < p_max; ++k, tail = t) {
        for (arma::uword i = 0; i < heads.n_rows; ++i) {
            arma::uword head = heads(i);
            heads(i) = t;
            for (arma::uword j = head; j < tail; ++j, ++t) {
                cinds(t) = (j < heads(i + 1)) ? (cinds(j) + 1) : 1;
                series[t] = 2.0 * series[j] / double(cinds(t));
            }
        }
    }
}
}
