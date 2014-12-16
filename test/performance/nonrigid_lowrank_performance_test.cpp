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
#include <cpd/nonrigid_lowrank.hpp>

#include "performance/fixtures.hpp"
#include "performance/timer.hpp"


namespace cpd
{
namespace test
{


class NonrigidLowrankPerformance : public PerformanceTest
{};


TEST_F(NonrigidLowrankPerformance, BasicRegistration)
{
    cpd::NonrigidLowrank reg;
    Timer timer;
    timer.start();
    cpd::Registration::ResultPtr result = reg.run(m_X, m_Y);
    timer.end();
    expect_matrices_near(m_Y_nonrigid_lowrank, result->Y, 1);
    std::cout << timer << std::endl;
}


}
}
