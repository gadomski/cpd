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

#include <cpd/nonrigid.hpp>

#include "registration_impl.hpp"
#include "test/support.hpp"

namespace cpd {

class NonrigidTest : public FishTest {};

TEST_F(NonrigidTest, StandaloneFunction) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    auto actual = nonrigid(m_fish1, m_fish2);
    ASSERT_EQ(expected.rows(), actual.points.rows());
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}

TEST_F(NonrigidTest, ClassBased) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    Nonrigid nonrigid;
    auto actual = nonrigid.compute(m_fish1, m_fish2);
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}

TEST_F(NonrigidTest, WithSigma2) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    auto actual = nonrigid(m_fish1, m_fish2, 1.0);
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}
}
