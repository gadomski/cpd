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
#include <cpd/affinity_matrix.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class AffinityMatrix : public RegistrationTest
{};


TEST_F(AffinityMatrix, MatchesReferenceImpl)
{
    arma::mat G;
    cpd::construct_affinity_matrix(m_Y, m_Y, 2, G);

    EXPECT_NEAR(1.0000, G(0), 0.0001);
    EXPECT_NEAR(0.0439, G(35, 0), 0.0001);
    EXPECT_NEAR(0.8825, G(3, 6), 0.0001);
    EXPECT_NEAR(1.0000, G(35, 35), 0.0001);
}


}
}
