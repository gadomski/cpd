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

#include "cpd/comparer/fgt.hpp"
#include "comparer/common.hpp"
#include "support.hpp"
#include "gtest/gtest.h"

namespace cpd {

TEST(FgtComparer, 2D) {
    FgtComparer comparer;
    auto fish = test_data_matrix("fish.csv");
    auto fish_distorted = test_data_matrix("fish-distorted.csv");
    Probabilities probabilities =
        comparer.compute(fish, fish_distorted, 1.0, 0.1);
    check_fish_probabilities(probabilities);
}

TEST(FgtComparer, 3D) {
    FgtComparer comparer;
    auto face = test_data_matrix("face.csv");
    auto face_distorted = test_data_matrix("face-distorted.csv");
    Probabilities probabilities =
        comparer.compute(face, face_distorted, 1.0, 0.1);
    check_face_probabilities(probabilities);
}
}
