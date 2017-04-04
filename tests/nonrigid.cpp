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

#include "fixtures/face.hpp"
#include "fixtures/fish.hpp"
#include "tests/support.hpp"
#include "gtest/gtest.h"
#include <cpd/nonrigid.hpp>

namespace cpd {

TEST_F(FishTest, Works) {
    NonrigidResult result = nonrigid(m_fish, m_fish_distorted);
    EXPECT_TRUE(result.points.isApprox(m_fish, 0.1));
}

TEST_F(FaceTest, Works) {
    Nonrigid nonrigid;
    nonrigid.normalize(false).sigma2(1.0).outliers(0.1);
    NonrigidResult result = nonrigid.run(m_face, m_face_distorted);
    EXPECT_TRUE(result.points.row(0).isApprox(m_face.row(0), 0.01));
    EXPECT_TRUE(result.points.row(391).isApprox(m_face.row(391), 0.5));
}

TEST(Nonrigid, Linked) {
    Nonrigid nonrigid;
    nonrigid.linked(true);
    EXPECT_TRUE(nonrigid.linked());
    nonrigid.linked(false);
    EXPECT_FALSE(nonrigid.linked());
}
} // namespace cpd
