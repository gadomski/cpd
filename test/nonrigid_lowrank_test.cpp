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

#pragma GCC diagnostic warning "-Wuninitialized"
#include <cpd/nonrigid_lowrank.hpp>
#pragma GCC diagnostic error "-Wuninitialized"

#include "fixtures.hpp"


namespace cpd {
namespace test {


class NonrigidLowrankRegistration : public RegistrationTest {};


TEST_F(NonrigidLowrankRegistration, InitializesWithDefaults) {
    cpd::NonrigidLowrank reg;
}


TEST_F(NonrigidLowrankRegistration, RegistersData) {
    cpd::NonrigidLowrank reg;
    reg.use_fgt(false); // to tighten up our tolerances
    reg.set_numeig(10); // becuase the default (M ^ (1/2) is too low)
    cpd::Registration::ResultPtr result = reg.run(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.1);
}


TEST_F(NonrigidLowrankRegistration, RegistersDataWithZExaggeration) {
    cpd::NonrigidLowrank reg;
    reg.use_fgt(false);
    reg.set_numeig(10);
    reg.set_z_exaggeration(2);
    cpd::Registration::ResultPtr result = reg.run(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.1);
}
}
}
