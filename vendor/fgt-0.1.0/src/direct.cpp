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

#include <fgt/fgt.hpp>


namespace fgt {


arma::vec Direct::compute_impl(const arma::mat& target,
                               const arma::vec& weights) const {
    double bandwidth2 = get_bandwidth() * get_bandwidth();
    const arma::mat& source = get_source();
    arma::vec g = arma::zeros<arma::vec>(target.n_rows);
    for (arma::uword j = 0; j < target.n_rows; ++j) {
        g(j) = arma::as_scalar(
            weights.t() *
            arma::exp(
                -arma::sum(arma::pow(source - arma::repmat(target.row(j),
                                                           source.n_rows, 1),
                                     2),
                           1) /
                bandwidth2));
    }
    return g;
}
}
