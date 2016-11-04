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

#include "cpd/comparer.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

template <typename Comparer>
class ComparerTest : public ::testing::Test {};

typedef ::testing::Types<DirectComparer, FgtComparer> ComparerTypes;
TYPED_TEST_CASE(ComparerTest, ComparerTypes);

TYPED_TEST(ComparerTest, 2D) {
    TypeParam computer;
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    Probabilities probabilities =
        computer.compute(fish, fish_distorted, 1.0, 0.1);
    ASSERT_EQ(91, probabilities.p1.size());
    EXPECT_NEAR(0.6850, probabilities.p1(0), 1e-4);
    EXPECT_NEAR(1.0689, probabilities.p1(90), 1e-4);
    ASSERT_EQ(91, probabilities.pt1.size());
    EXPECT_NEAR(0.9882, probabilities.pt1(0), 1e-4);
    EXPECT_NEAR(0.9869, probabilities.pt1(90), 1e-4);
    ASSERT_EQ(91, probabilities.px.rows());
    ASSERT_EQ(2, probabilities.px.cols());
    EXPECT_NEAR(-0.2625, probabilities.px(0, 0), 1e-4);
    EXPECT_NEAR(-0.3164, probabilities.px(90, 1), 1e-4);
    EXPECT_NEAR(-338.4930, probabilities.l, 1e-3);
}

TEST(DirectComparer, Correspondence) {
    DirectComparer computer;
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    IndexVector correspondence =
        test_data_matrix("fish-correspondence.csv").cast<Matrix::Index>();
    Probabilities probabilities =
        computer.compute(fish, fish_distorted, 1.0, 0.1);
    EXPECT_EQ(correspondence.size(), probabilities.correspondence.size());
    EXPECT_EQ(correspondence, probabilities.correspondence);
}

TYPED_TEST(ComparerTest, 3D) {
    TypeParam computer;
    auto face = test_data_matrix("face.csv");
    auto face_distorted = test_data_matrix("face-distorted.csv");
    Probabilities probabilities =
        computer.compute(face, face_distorted, 1.0, 0.1);
    ASSERT_EQ(392, probabilities.p1.size());
    EXPECT_NEAR(0.6171, probabilities.p1(0), 1e-4);
    EXPECT_NEAR(0.4869, probabilities.p1(391), 1e-4);
    ASSERT_EQ(392, probabilities.pt1.size());
    EXPECT_NEAR(0.9850, probabilities.pt1(0), 1e-4);
    EXPECT_NEAR(0.9823, probabilities.pt1(391), 1e-4);
    ASSERT_EQ(392, probabilities.px.rows());
    ASSERT_EQ(3, probabilities.px.cols());
    EXPECT_NEAR(-0.2361, probabilities.px(0, 0), 1e-4);
    EXPECT_NEAR(-0.0271, probabilities.px(391, 2), 1e-4);
    EXPECT_NEAR(-2.0397e3, probabilities.l, 1e-1);
}
}
