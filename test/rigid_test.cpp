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
#include <cpd/rigid.hpp>
#pragma GCC diagnostic error "-Wuninitialized"


#include "fixtures.hpp"


namespace cpd {
namespace test {


class RigidRegistration : public RegistrationTest {};


TEST_F(RigidRegistration, InitializesWithDefaults) { cpd::Rigid reg; }


TEST_F(RigidRegistration, RegistersData) {
    cpd::Rigid reg;
    reg.use_fgt(false); // to tighten up our tolerances
    cpd::Registration::ResultPtr result = reg.run(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.001);
}


TEST_F(RigidRegistration, TransformationMatrix) {
    cpd::Rigid reg;
    reg.use_fgt(false);
    cpd::Registration::ResultPtr result = reg.run(m_X, m_Y);
    arma::mat transformation_matrix = {3.6e-1, -8e-1, 4.8e-1, 0, 4.8e-1, 6e-1,
                                       6.4e-1, 0,     -8e-1,  0, 6e-1,   0,
                                       0,      0,     0,      1};
    transformation_matrix.reshape(4, 4);
    transformation_matrix = transformation_matrix.t();
    expect_matrices_near(transformation_matrix, result->transformation, 0.001);
}
}
}
