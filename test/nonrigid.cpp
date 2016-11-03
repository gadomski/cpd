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

#include "cpd/nonrigid.hpp"
#include "cpd/runner.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

TEST(Nonrigid, 2D) {
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    Runner<Nonrigid, DirectProbabilityComputer> runner;
    auto result = runner.run(fish, fish_distorted);
    EXPECT_TRUE(result.points.isApprox(fish, 0.1));
}

TEST(Nonrigid, 3D) {
    auto face = test_data_matrix("face.csv");
    auto face_distorted = test_data_matrix("face-distorted.csv");
    Runner<Nonrigid, DirectProbabilityComputer> runner;
    runner.normalize(false).sigma2(1.0).outliers(0.1);
    auto result = runner.run(face, face_distorted);
    EXPECT_TRUE(result.points.row(0).isApprox(face.row(0), 0.01));
    EXPECT_TRUE(result.points.row(391).isApprox(face.row(391), 0.5));
}
}
