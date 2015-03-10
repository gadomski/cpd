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

#pragma once

#include <armadillo>

#include "config.hpp"


namespace cpd {
namespace test {


class PerformanceTest : public ::testing::Test {
public:
    virtual void SetUp() {
        read_data_file("140712_003331.txt", m_X);
        read_data_file("140712_064332.txt", m_Y);
        read_data_file("140712_064332_rigid.txt", m_Y_rigid);
        read_data_file("140712_064332_nonrigid_lowrank.txt",
                       m_Y_nonrigid_lowrank);
    }

    arma::mat m_X;
    arma::mat m_Y;
    arma::mat m_Y_rigid;
    arma::mat m_Y_nonrigid_lowrank;
};
}
}
