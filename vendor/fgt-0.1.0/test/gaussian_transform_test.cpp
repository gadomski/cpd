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

#include <fgt/exceptions.hpp>

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


class MockGaussTransform : public GaussTransform {
public:
    using GaussTransform::GaussTransform;

private:
    virtual arma::vec compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const override {
        return arma::zeros<arma::vec>(target.n_rows);
    }
};


TEST(GaussTransform, IncorrectDimensions) {
    arma::mat source(1, 2);
    arma::mat target(1, 3);
    double bandwidth = 1;
    MockGaussTransform transform(source, bandwidth);
    EXPECT_THROW(transform.compute(target), dimension_mismatch);
}


TEST(GaussTransform, IncorrectWeightCount) {
    arma::mat source(1, 2);
    arma::mat target(1, 2);
    arma::vec weights(2);
    double bandwidth = 1;
    MockGaussTransform transform(source, bandwidth);
    EXPECT_THROW(transform.compute(target, weights), dimension_mismatch);
}
}
