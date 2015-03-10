/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#include <gtest/gtest.h>
#include "affinity_eigenvectors.hpp"

#include "fixtures.hpp"


namespace cpd {
namespace test {


class AffinityEigenvectors : public RegistrationTest {};


TEST_F(AffinityEigenvectors, MatchesReferenceImpl) {
    arma::mat Q, S;
    cpd::find_affinity_eigenvectors(m_Y, 2, 10, 1e-4, Q, S);

    EXPECT_NEAR(0.1651, std::abs(Q(0)), 0.0001);
    EXPECT_NEAR(0.1978, std::abs(Q(35, 9)), 0.0001);
    EXPECT_NEAR(16.5205, S(0, 0), 0.01);
    EXPECT_NEAR(0.3057, S(9, 9), 0.01);
}
}
}
