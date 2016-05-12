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

#include "test/support.hpp"
#include "utils.hpp"

namespace cpd {

class UtilsTest : public FishTest {};

TEST_F(UtilsTest, DefaultSigma2) {
    double sigma2 = default_sigma2(m_fish1, m_fish2);
    EXPECT_NEAR(3.5, sigma2, 1e-8);
}

TEST_F(UtilsTest, G) {
    Matrix expected = load_test_data_matrix("fish-G.txt");
    Matrix actual = construct_affinity_matrix(m_fish2, m_fish2, 3);
    std::cout << actual << std::endl;
    EXPECT_EQ(expected.size(), actual.size());
    EXPECT_TRUE(expected.isApprox(actual, 1e-4));
}
}
