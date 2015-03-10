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

#include <fgt/fgt.hpp>

#include "config.hpp"

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt
{


TEST(DirectTree, ReferenceImplementation)
{
    arma::mat source, target;
    source.load(test_data_path("X.csv"));
    source.resize(1000, source.n_cols);
    target.load(test_data_path("Y.csv"));
    target.resize(1000, target.n_cols);
    double bandwidth = 0.4;
    double epsilon = 1e-3;
    arma::vec weights = arma::ones<arma::vec>(source.n_rows);

    DirectTree direct_tree(source, bandwidth, epsilon);
    arma::vec g = direct_tree.compute(target, weights);

    EXPECT_EQ(1000, g.n_rows);
    EXPECT_DOUBLE_EQ(557.19832513213646, g(0));
}


}
