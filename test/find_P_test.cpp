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
#include "find_P.hpp"

#include "fixtures.hpp"


namespace cpd {
namespace test {


class FindP : public RegistrationTest {};


TEST_F(FindP, MatchesReferenceImplWithoutFGT) {
    arma::mat PX(m_Y.n_rows, m_Y.n_cols);
    arma::vec P1(m_Y.n_rows), Pt1(m_Y.n_rows);
    double L =
        cpd::find_P(m_X, m_Y, 0.6666666667, 0.1, P1, Pt1, PX, false, 1e-4);

    EXPECT_NEAR(0.9352, P1(0), 0.0001);
    EXPECT_NEAR(0.1106, P1(35), 0.0001);

    EXPECT_NEAR(0.7806, Pt1(0), 0.0001);
    EXPECT_NEAR(0.3238, Pt1(35), 0.0001);

    EXPECT_NEAR(0.4230, PX(0), 0.0001);
    EXPECT_NEAR(0.4233, PX(35, 2), 0.0001);

    EXPECT_NEAR(-52.4994, L, 0.0001);
}
}
}
