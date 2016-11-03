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

#include "affinity_matrix.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

TEST(AffinityMatrix, Fish) {
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    auto matrix = affinity_matrix(fish, fish_distorted, 3.0);
    ASSERT_EQ(91, matrix.rows());
    ASSERT_EQ(91, matrix.cols());
    EXPECT_NEAR(0.9911, matrix(0, 0), 1e-4);
    EXPECT_NEAR(0.9969, matrix(90, 90), 1e-4);
}
}
