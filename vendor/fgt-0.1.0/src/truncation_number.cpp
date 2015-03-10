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

#include "truncation_number.hpp"

#include <cmath>


namespace fgt {


arma::uword choose_truncation_number(double distance2, double cutoff_radius,
                                     double bandwidth, double epsilon,
                                     arma::uword max_truncation_number) {
    double distance = std::sqrt(distance2);
    double bandwidth2 = bandwidth * bandwidth;
    double error = epsilon + 1;
    double temp = 1;
    arma::uword truncation_number = 0;

    while (error > epsilon and truncation_number < max_truncation_number) {
        ++truncation_number;
        double b = std::min(
            (distance +
             std::sqrt(distance2 + 2 * truncation_number * bandwidth2)) /
                2,
            cutoff_radius);
        double c = distance - b;
        temp *= 2 * distance * b / bandwidth2 / double(truncation_number);
        error = temp * std::exp(-c * c / bandwidth2);
    }
    return truncation_number;
}
}
