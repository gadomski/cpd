// cpd - Coherent Point Drift
// Copyright (C) 2016 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "cpd/utils.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

TEST(Utils, DefaultSigma2) {
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    double sigma2 = default_sigma2(fish, fish_distorted);
    EXPECT_NEAR(1.0, sigma2, 0.1);
}

TEST(Utils, Sigma2SamePoints) {
    auto fish = test_data_matrix("fish.csv");
    double sigma2 = default_sigma2(fish, fish);
    EXPECT_NEAR(1.0, sigma2, 0.001);
}

TEST(Utils, Sigma2Helheim) {
    auto helheim = test_data_matrix("helheim.csv");
    double sigma2 = default_sigma2(helheim, helheim);
    EXPECT_NEAR(23235, sigma2, 1.0);
}

TEST(Utils, MatrixFromFile) {
    auto fish = test_data_matrix("fish.csv");
    EXPECT_EQ(91, fish.rows());
    EXPECT_EQ(2, fish.cols());
    EXPECT_NEAR(-0.91542, fish(0, 0), 1e-5);
    EXPECT_NEAR(-0.75806, fish(90, 1), 1e-5);
}
}
