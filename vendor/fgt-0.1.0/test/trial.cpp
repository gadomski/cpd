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

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


class Trial : public ::testing::TestWithParam<double> {
protected:
    static const arma::uword NumSourceRows = 1000;
    static const arma::uword NumTargetRows = 1000;
    static const arma::uword NumCols = 3;
    constexpr static const double Epsilon = 1e-2;

    Trial()
        : ::testing::TestWithParam<double>(),
          m_source(arma::randu<arma::mat>(NumSourceRows, NumCols)),
          m_target(arma::randu<arma::mat>(NumTargetRows, NumCols)),
          m_weights(arma::randu<arma::vec>(NumSourceRows)),
          m_weights_sum(arma::sum(m_weights)),
          m_epsilon(Epsilon) {}

    arma::mat m_source, m_target;
    arma::vec m_weights;
    double m_weights_sum;
    double m_epsilon;
};


TEST_P(Trial, AllMethods) {
    Direct direct(m_source, GetParam());
    arma::vec g_direct = direct.compute(m_target, m_weights);

    DirectTree direct_tree(m_source, GetParam(), m_epsilon);
    arma::vec g_direct_tree = direct_tree.compute(m_target, m_weights);

    Ifgt ifgt(m_source, GetParam(), m_epsilon);
    arma::vec g_ifgt = ifgt.compute(m_target, m_weights);

    Ifgt ifgt_data_adaptive(m_source, GetParam(), m_epsilon);
    ifgt.use_data_adaptive_truncation(true);
    arma::vec g_ifgt_data_adaptive =
        ifgt_data_adaptive.compute(m_target, m_weights);

    double error_direct_tree =
        arma::max(arma::abs(g_direct_tree - g_direct) / m_weights_sum);
    double error_ifgt = arma::max(arma::abs(g_ifgt - g_direct) / m_weights_sum);
    double error_ifgt_data_adaptive =
        arma::max(arma::abs(g_ifgt_data_adaptive - g_direct) / m_weights_sum);

    EXPECT_GT(m_epsilon, error_direct_tree);
    EXPECT_GT(m_epsilon, error_ifgt);
    EXPECT_GT(m_epsilon, error_ifgt_data_adaptive);
}


INSTANTIATE_TEST_CASE_P(Trial, Trial, ::testing::Values(0.01, 0.02, 0.04, 0.08,
                                                        0.16, 0.32, 0.64));
}
