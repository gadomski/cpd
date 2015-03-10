// fgt, C++ library for Fast Gauss Transforms
// Copyright (C) 2015 Peter J. Gadomski <pete.gadomski@gmail.com>
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

#include "truncation_number.hpp"

#include <gtest/gtest.h>

#include <cmath>


namespace fgt
{


TEST(ChooseTruncationNumber, ReferenceImplementation) {
    double bandwidth = 0.3;
    double epsilon = 1e-6;
    double distance2 = 0.01;
    double cutoff_radius = std::sqrt(distance2) + bandwidth * std::sqrt(std::log(1 / epsilon));
    arma::uword max_truncation_number = 300;
    int p_max = choose_truncation_number(distance2, cutoff_radius, bandwidth, epsilon);
    EXPECT_EQ(9, p_max);
}


}
