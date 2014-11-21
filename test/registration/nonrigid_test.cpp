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

#include <gtest/gtest.h>
#include <cpd/registration/nonrigid.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class NonrigidRegistration : public RegistrationTest
{};


TEST_F(NonrigidRegistration, InitializesWithDefaults)
{
    cpd::registration::Nonrigid reg;
}


TEST_F(NonrigidRegistration, RegistersData)
{
    cpd::registration::Nonrigid reg;
    reg.use_fgt(false); // to tighten up our tolerances
    cpd::registration::SpResult result = reg(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.0001);
}


}
}
