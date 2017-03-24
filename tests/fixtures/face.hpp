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

#include "tests/support.hpp"
#include "gtest/gtest.h"

namespace cpd {

class FaceTest : public ::testing::Test {
public:
    FaceTest()
      : ::testing::Test()
      , m_face(tests::fixture("face.csv"))
      , m_face_distorted(tests::fixture("face_distorted.csv")) {}

    Matrix m_face;
    Matrix m_face_distorted;
};
} // namespace cpd
