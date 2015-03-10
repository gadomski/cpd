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

#include "monomials.hpp"

#include "p_max_total.hpp"

#include <armadillo>
#include <gtest/gtest.h>

#include <vector>


namespace fgt {


TEST(Monomials, ReferenceImplementation) {
    arma::rowvec dx = {0.319529, 0.401860};
    arma::uword p_max = 70;
    std::vector<double> monomials(get_p_max_total(2, p_max));
    compute_monomials(dx / 0.4, p_max, monomials);

    EXPECT_EQ(2485, monomials.size());
    EXPECT_NEAR(1.0, monomials.at(0), 0.000001);
    EXPECT_NEAR(0.798823, monomials.at(1), 0.000001);
    EXPECT_NEAR(1.004649, monomials.at(2), 0.000001);
    EXPECT_NEAR(0.638118, monomials.at(3), 0.000001);
    EXPECT_NEAR(0.802537, monomials.at(4), 0.000001);
    EXPECT_NEAR(1.009321, monomials.at(5), 0.000001);
}
}
