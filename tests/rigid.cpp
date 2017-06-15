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

#define _USE_MATH_DEFINES

#include "fixtures/fish.hpp"
#include "gtest/gtest.h"
#include <cpd/rigid.hpp>
#include <cmath>

namespace cpd {

TEST_F(FishTest, ComputeOneMatchesReference) {
    GaussTransformDirect direct;
    Probabilities probabilities =
        direct.compute(m_fish, m_fish_distorted, 1.0, 0.1);
    Rigid rigid;
    rigid.scale(true);
    RigidResult result =
        rigid.compute_one(m_fish, m_fish_distorted, probabilities, 1.0);
    EXPECT_NEAR(0.4165, result.sigma2, 1e-2);

    rigid.scale(false);
    result = rigid.compute_one(m_fish, m_fish_distorted, probabilities, 1.0);
    EXPECT_NEAR(0.5238, result.sigma2, 1e-2);
}

TEST_F(FishTest, Normalize) {
    m_fish = m_fish * 10.0;
    Matrix rotation =
        Eigen::Rotation2D<double>(M_PI * 20.0 / 180.0).toRotationMatrix();
    m_fish_distorted = m_fish * rotation;
    RigidResult result = rigid(m_fish_distorted, m_fish);
    EXPECT_TRUE(result.rotation.isApprox(rotation.transpose(), 1e-4));
    EXPECT_EQ(result.points.rows(), m_fish.rows());
}

TEST_F(FishTest, Scale) {
    m_fish_distorted = m_fish * 10.0;
    Rigid rigid;
    rigid.scale(true);
    RigidResult result = rigid.run(m_fish_distorted, m_fish);
    EXPECT_NEAR(10.0, result.scale, 0.1);
}

TEST(Rigid, Linked) {
    Rigid rigid;
    rigid.scale(true);
    EXPECT_FALSE(rigid.linked());
    rigid.scale(false);
    EXPECT_TRUE(rigid.linked());
}

TEST_F(FishTest, OneMatrix) {
    RigidResult result = rigid(m_fish_distorted, m_fish);
    Matrix transform = result.matrix();
    ASSERT_EQ(transform.rows(), 3);
    ASSERT_EQ(transform.cols(), 3);
    Matrix fish = apply_transformation_matrix(m_fish, transform);
    EXPECT_TRUE(result.points.isApprox(fish, 1e-4));
}
} // namespace cpd
