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

#include <Eigen/Geometry>

#include "cpd/comparer/direct.hpp"
#include "cpd/matrix.hpp"
#include "cpd/rigid.hpp"
#include "cpd/runner.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

const double TOLERANCE = 1e-3;

class FishRotationTest : public FishTest,
                         public ::testing::WithParamInterface<double> {
public:
    FishRotationTest()
      : FishTest()
      , m_rotation(Eigen::Rotation2D<double>(M_PI * GetParam() / 180.0)
                       .toRotationMatrix()) {
        m_fish_transformed = m_fish * m_rotation;
    }

    Matrix m_rotation;
};

class FishTranslationTest : public FishTest,
                            public ::testing::WithParamInterface<double> {
public:
    FishTranslationTest()
      : FishTest()
      , m_translation(Eigen::Vector2d(GetParam(), GetParam())) {
        m_fish_transformed =
            m_fish + m_translation.transpose().replicate(m_fish.rows(), 1);
    }

    Vector m_translation;
};

TEST_F(FishTest, AllowScaling) {
    m_fish_transformed = test_data_matrix("fish-distorted.csv");
    DirectComparer comparer;
    Probabilities probabilities =
        comparer.compute(m_fish, m_fish_transformed, 1.0, 0.1);
    Rigid rigid;
    rigid.scale(true);
    auto result = rigid.compute(m_fish, m_fish_transformed, probabilities, 1.0);
    EXPECT_NEAR(0.4165, result.sigma2, 1e-2);
}

TEST_F(FishTest, NoScaling) {
    m_fish_transformed = test_data_matrix("fish-distorted.csv");
    DirectComparer computer;
    Probabilities probabilities =
        computer.compute(m_fish, m_fish_transformed, 1.0, 0.1);
    Rigid rigid;
    rigid.scale(false);
    auto result = rigid.compute(m_fish, m_fish_transformed, probabilities, 1.0);
    EXPECT_NEAR(0.5238, result.sigma2, 1e-2);
}

TEST_F(FishTest, Normalize) {
    m_fish = m_fish * 10.0;
    Matrix rotation =
        Eigen::Rotation2D<double>(M_PI * 20.0 / 180.0).toRotationMatrix();
    m_fish_transformed = m_fish * rotation;
    auto result = rigid(m_fish_transformed, m_fish);
    EXPECT_TRUE(result.rotation.isApprox(rotation.transpose(), TOLERANCE));
    EXPECT_EQ(result.points.rows(), m_fish.rows());
}

TEST_F(FishTest, DifferentlySized) {
    Runner<Rigid> runner;
    runner.normalize(false);
    Rigid::Result result = runner.run(
        m_fish, m_fish.block(0, 0, m_fish.rows() - 1, m_fish.cols()));
    EXPECT_EQ(m_fish.rows() - 1, result.points.rows());
}

TEST_P(FishRotationTest, IsRecovered) {
    auto result = rigid(m_fish_transformed, m_fish);
    EXPECT_TRUE(result.rotation.isApprox(m_rotation.transpose(), TOLERANCE));
}

TEST_P(FishTranslationTest, IsRecovered) {
    auto result = rigid(m_fish_transformed, m_fish);
    EXPECT_TRUE(result.translation.isApprox(m_translation, TOLERANCE));
}

INSTANTIATE_TEST_CASE_P(Fish, FishRotationTest,
                        ::testing::Range(0.0, 70.0, 10.0));
INSTANTIATE_TEST_CASE_P(Fish, FishTranslationTest, ::testing::Range(1.0, 10.0));

class FaceRotationTest : public FaceTest,
                         public ::testing::WithParamInterface<double> {
public:
    FaceRotationTest()
      : FaceTest()
      , m_rotation(Eigen::AngleAxisd(GetParam() * M_PI / 180.0,
                                     Eigen::Vector3d::UnitX())
                       .toRotationMatrix()) {
        m_face_transformed = m_face * m_rotation;
    }

    Matrix m_rotation;
};

class FaceTranslationTest : public FaceTest,
                            public ::testing::WithParamInterface<double> {
public:
    FaceTranslationTest()
      : FaceTest()
      , m_translation(Eigen::Vector3d(GetParam(), GetParam(), GetParam())) {
        m_face_transformed =
            m_face +
            m_translation.transpose().replicate(m_face_transformed.rows(), 1);
    }

    Vector m_translation;
};

TEST_P(FaceRotationTest, IsRecovered) {
    auto result = rigid(m_face_transformed, m_face);
    EXPECT_TRUE(result.rotation.isApprox(m_rotation.transpose(), TOLERANCE));
}

TEST_P(FaceTranslationTest, IsRecovered) {
    auto result = rigid(m_face_transformed, m_face);
    EXPECT_TRUE(result.translation.isApprox(m_translation, TOLERANCE));
}

INSTANTIATE_TEST_CASE_P(Face, FaceRotationTest,
                        ::testing::Range(0.0, 70.0, 10.0));
INSTANTIATE_TEST_CASE_P(Face, FaceTranslationTest, ::testing::Range(1.0, 10.0));
}
