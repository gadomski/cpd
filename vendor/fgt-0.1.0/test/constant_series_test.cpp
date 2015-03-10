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

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


TEST(ConstantSeries, ReferenceImplementation) {
    arma::uword d = 2;
    arma::uword p_max = 70;
    std::vector<double> series(get_p_max_total(d, p_max));
    compute_constant_series(2, 70, series);
    EXPECT_EQ(2485, series.size());
    EXPECT_DOUBLE_EQ(1, series.at(0));
    EXPECT_DOUBLE_EQ(2, series.at(1));
    EXPECT_DOUBLE_EQ(2, series.at(2));
    EXPECT_DOUBLE_EQ(2, series.at(3));
    EXPECT_DOUBLE_EQ(4, series.at(4));
    EXPECT_DOUBLE_EQ(2, series.at(5));
    EXPECT_DOUBLE_EQ(4.0 / 3.0, series.at(6));
}
}
