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
#include "gtest/gtest.h"
#include <cpd/normalization.hpp>

namespace cpd {

TEST_F(FishTest, CanBeRetrieved) {
    Normalization normalization(m_fish, m_fish);
    ASSERT_EQ(m_fish.rows(), normalization.fixed.rows());
    EXPECT_TRUE(
        m_fish.isApprox(normalization.fixed * normalization.fixed_scale +
                            normalization.fixed_mean.transpose().replicate(
                                normalization.fixed.rows(), 1),
                        1e-4));
}

TEST_F(FishTest, Unlinked) {
    Normalization normalization(m_fish, m_fish * 2, false);
    EXPECT_NEAR(normalization.fixed_scale, normalization.moving_scale / 2.0,
                1e-4);
}
} // namespace cpd
