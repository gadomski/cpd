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

#include "config.hpp"

#include <gtest/gtest.h>


namespace cpd
{
namespace test
{


std::string data_file_path(const std::string& filename)
{
    return CPD_TEST_DATA_DIR + "/" + filename;
}


void read_data_file(const std::string& filename, arma::mat& m)
{
    m.quiet_load(test::data_file_path(filename));    
}


void expect_matrices_near(const arma::mat& X, const arma::mat& Y, double tolerance)
{
    EXPECT_EQ(X.n_elem, Y.n_elem);
    typedef arma::mat::const_iterator it_t;
    for (it_t itX = X.begin(), itY = Y.begin();
            itX != X.end() && itY != Y.end();
            ++itX, ++itY)
    {
        EXPECT_NEAR(*itX, *itY, tolerance);
    }
}


}
}
