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

#include "normalization.hpp"
#include "test/support.hpp"

namespace cpd {

class NormalizationTest : public FishTest {};

TEST_F(NormalizationTest, SourceTargetRows) {
    Normalization normalization(m_fish1, m_fish2, 1.0);
    EXPECT_EQ(m_fish1.rows(), normalization.source().rows());
    EXPECT_EQ(m_fish2.rows(), normalization.target().rows());
    EXPECT_GT(1.0, normalization.sigma2());
}
}
