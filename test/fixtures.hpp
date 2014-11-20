/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
* 
* Derived from the Coherent Point Drift Matlab package
* Copyright (C) 2008-2009 Andriy Myronenko <myron@csee.ogi.edu>
* https://sites.google.com/site/myronenko/research/cpd
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

#include <armadillo>


namespace cpd
{
namespace test
{


class RegistrationTest : public ::testing::Test
{
public:

    virtual void SetUp()
    {
        m_X << 0 << 0 << 0 << arma::endr
            << 1 << 0 << 0 << arma::endr
            << 2 << 0 << 0 << arma::endr
            << 0 << 1 << 0 << arma::endr
            << 1 << 1 << 0 << arma::endr
            << 2 << 1 << 0 << arma::endr
            << 0 << 2 << 0 << arma::endr
            << 1 << 2 << 0 << arma::endr
            << 2 << 2 << 0 << arma::endr
            << 0 << 3 << 0 << arma::endr
            << 1 << 3 << 0 << arma::endr
            << 2 << 3 << 0 << arma::endr
            << 0 << 0 << 1 << arma::endr
            << 1 << 0 << 1 << arma::endr
            << 2 << 0 << 1 << arma::endr
            << 0 << 0 << 2 << arma::endr
            << 1 << 0 << 2 << arma::endr
            << 2 << 0 << 2 << arma::endr
            << 0 << 0 << 3 << arma::endr
            << 1 << 0 << 3 << arma::endr
            << 2 << 0 << 3 << arma::endr
            << 0 << 0 << 4 << arma::endr
            << 1 << 0 << 4 << arma::endr
            << 2 << 0 << 4 << arma::endr
            << 0 << 1 << 1 << arma::endr
            << 0 << 2 << 1 << arma::endr
            << 0 << 3 << 1 << arma::endr
            << 0 << 1 << 2 << arma::endr
            << 0 << 2 << 2 << arma::endr
            << 0 << 3 << 2 << arma::endr
            << 0 << 1 << 3 << arma::endr
            << 0 << 2 << 3 << arma::endr
            << 0 << 3 << 3 << arma::endr
            << 0 << 1 << 4 << arma::endr
            << 0 << 2 << 4 << arma::endr
            << 0 << 3 << 4 << arma::endr;
        // TODO randomize?
        m_R << 0.36 << 0.48 << -0.8 << arma::endr
            << -0.8 << 0.60 << 0.00 << arma::endr
            << 0.48 << 0.64 << 0.60 << arma::endr;
        m_Y = m_X * m_R.t();
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

    arma::mat::fixed<36, 3> m_X;
    arma::mat::fixed<36, 3> m_Y;
    arma::mat33 m_R;

};


}
}
