// cpd - Coherent Point Drift
// Copyright (C) 2017 Pete Gadomski <pete.gadomski@gmail.com>
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

#include "fixtures/fish.hpp"
#include "fixtures/helheim.hpp"
#include "gtest/gtest.h"

namespace cpd {
TEST_F(FishTest, DefaultSigma2) {
    double sigma2 = cpd::default_sigma2(m_fish, m_fish_distorted);
    EXPECT_NEAR(1.0, sigma2, 0.1);
}

TEST_F(HelheimTest, DefaultSigma2) {
    double sigma2 = cpd::default_sigma2(m_helheim, m_helheim);
    EXPECT_NEAR(23235., sigma2, 1.0);
}

TEST_F(FishTest, AffinityMatrix) {
    Matrix matrix = cpd::affinity(m_fish, m_fish_distorted, 3.0);
    ASSERT_EQ(91, matrix.rows());
    ASSERT_EQ(91, matrix.cols());
    EXPECT_NEAR(0.9911, matrix(0, 0), 1e-4);
    EXPECT_NEAR(0.9969, matrix(90, 90), 1e-4);
}
} // namespace cpd
