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
#include "sigma2.hpp"


namespace cpd
{
namespace test
{


TEST(Sigma2, MatchesReferenceImpl)
{
    arma::mat33 X, Y;
    X << 1 << 2 << 3 << arma::endr
      << 4 << 5 << 6 << arma::endr
      << 7 << 8 << 9 << arma::endr;
    Y << 10 << 11 << 12 << arma::endr
      << 13 << 14 << 15 << arma::endr
      << 16 << 17 << 18 << arma::endr;
    EXPECT_DOUBLE_EQ(93, calculate_sigma2(X, Y));
}


}
}
