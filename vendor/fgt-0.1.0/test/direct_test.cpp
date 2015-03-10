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

#include "config.hpp"

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


TEST(Direct, OneTargetOneSource) {
    arma::mat source = {0, 0};
    source.reshape(1, 2);
    arma::mat target = {1, 2};
    target.reshape(1, 2);

    Direct direct(source, 1);
    arma::vec g = direct.compute(target);
    EXPECT_EQ(g.n_rows, 1);
    EXPECT_DOUBLE_EQ(0.006737946999085467, g(0));
}


TEST(Direct, TwoTargetsTwoSources) {
    arma::mat source = {0, 0, 0, 1};
    source.reshape(2, 2);
    arma::mat target = {0, 0.5, 0.25, 0.25};
    target.reshape(2, 2);

    Direct direct(source, 0.2);
    arma::vec g = direct.compute(target);
    EXPECT_EQ(g.n_rows, 2);
    EXPECT_DOUBLE_EQ(0.2096121683000387, g(0));
    EXPECT_DOUBLE_EQ(0.00040464667729846903, g(1));
}
}
