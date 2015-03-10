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

#include "clustering.hpp"
#include "config.hpp"

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


TEST(ChooseIfgtParameters, LargeKLimit) {
    int d = 2;
    double h = 0.3;
    double epsilon = 1e-6;
    int k_limit = 189;
    Ifgt::Parameters params = Ifgt::choose_parameters(d, h, epsilon, k_limit);
    EXPECT_EQ(13, params.num_clusters);
    EXPECT_NEAR(1.1151, params.radius, 0.0001);
}


TEST(ChooseIfgtParameters, SmallKLimit) {
    arma::uword d = 2;
    double h = 0.4;
    double epsilon = 1e-3;
    arma::uword k_limit = 50;
    Ifgt::Parameters params = Ifgt::choose_parameters(d, h, epsilon, k_limit);
    EXPECT_EQ(15, params.num_clusters);
    EXPECT_NEAR(1.051304, params.radius, 0.000001);
}


TEST(ChooseIfgtParameters, NoBoundFound) {
    int d = 3;
    double h = 0.01;
    double epsilon = 1e-2;
    int k_limit = 189;
    Ifgt::Parameters params = Ifgt::choose_parameters(d, h, epsilon, k_limit);
    EXPECT_EQ(k_limit, params.num_clusters);
}


TEST(Ifgt, ReferenceImplementation) {
    arma::mat source, target;
    source.load(test_data_path("X.csv"));
    target.load(test_data_path("Y.csv"));
    double bandwidth = 0.4;
    double epsilon = 1e-3;
    arma::vec weights = arma::ones<arma::vec>(source.n_rows);
    int k_limit = 50;

    Ifgt ifgt(source, bandwidth, epsilon, k_limit);
    ifgt.set_clustering_starting_index(2);
    arma::vec g = ifgt.compute(target, weights);

    EXPECT_EQ(5000, g.n_rows);
    EXPECT_DOUBLE_EQ(2.071868804956274e+03, g(0));
}


TEST(Ifgt, DataAdaptiveReferenceImplementation) {
    arma::mat source, target;
    source.load(test_data_path("X.csv"));
    target.load(test_data_path("Y.csv"));
    double bandwidth = 0.4;
    double epsilon = 1e-3;
    arma::vec weights = arma::ones<arma::vec>(source.n_rows);
    int k_limit = 50;

    Ifgt ifgt(source, bandwidth, epsilon, k_limit);
    ifgt.set_clustering_starting_index(2).use_data_adaptive_truncation(true);
    arma::vec g = ifgt.compute(target, weights);

    EXPECT_EQ(5000, g.n_rows);
    EXPECT_DOUBLE_EQ(2071.7022219052133, g(0));
}
}
