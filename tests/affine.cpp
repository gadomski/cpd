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

#include "fixtures/face.hpp"
#include "fixtures/fish.hpp"
#include "gtest/gtest.h"
#include <cpd/affine.hpp>

namespace cpd {

TEST_F(FishTest, MatchesReference) {
    Matrix transform = Matrix(2, 2);
    transform << 1.2688, 0.9169, 1.1294, 1.4311;
    Vector translation = Vector(2);
    translation << 1., 2.;
    m_fish_distorted = m_fish * transform +
                       translation.transpose().replicate(m_fish.rows(), 1);
    AffineResult result = affine(m_fish_distorted, m_fish);
    ASSERT_EQ(result.points.rows(), m_fish.rows());
    EXPECT_TRUE(result.points.isApprox(m_fish_distorted, 1e-4));
    EXPECT_TRUE(result.transform.isApprox(transform.transpose(), 1e-4));
    EXPECT_TRUE(result.translation.isApprox(translation, 1e-4));
}

TEST_F(FaceTest, Affine) {
    Matrix transform = Matrix(3, 3);
    transform << 0.8240, -0.6682, 0.0845, 0.3796, 0.4136, -0.8015, 0.7927,
        0.8303, 0.5005;
    Vector translation = Vector(3);
    translation << 1.0, 2.0, 3.0;
    m_face_distorted = m_face * transform +
                       translation.transpose().replicate(m_face.rows(), 1);
    AffineResult result = affine(m_face_distorted, m_face);
    ASSERT_EQ(result.points.rows(), m_face.rows());
    EXPECT_TRUE(result.points.isApprox(m_face_distorted, 1e-4));
    EXPECT_TRUE(result.transform.isApprox(transform.transpose(), 1e-4));
    EXPECT_TRUE(result.translation.isApprox(translation, 1e-4));
}

TEST(Affine, Linked) {
    Affine affine;
    affine.linked(true);
    EXPECT_TRUE(affine.linked());
    affine.linked(false);
    EXPECT_FALSE(affine.linked());
}

TEST_F(FishTest, AffineMatrix) {
    AffineResult result = affine(m_fish_distorted, m_fish);
    Matrix transform = result.matrix();
    ASSERT_EQ(transform.rows(), 3);
    ASSERT_EQ(transform.cols(), 3);
    Matrix fish = apply_transformation_matrix(m_fish, transform);
    EXPECT_TRUE(result.points.isApprox(fish, 1e-4));
}
} // namespace cpd
