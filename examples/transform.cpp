// cpd - Coherent Point Drift
// Copyright (C) 2017 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <cpd/affine.hpp>
#include <cpd/rigid.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "ERROR: invalid usage" << std::endl;
        return 1;
    }
    cpd::Matrix fixed = cpd::matrix_from_path(argv[2]);
    cpd::Matrix moving = cpd::matrix_from_path(argv[3]);
    if (std::strcmp(argv[1], "rigid") == 0) {
        cpd::Rigid rigid;
        rigid.scale(true);
        cpd::RigidResult result = rigid.run(fixed, moving);
        cpd::Matrix transform = result.matrix();
        std::cout << transform << std::endl;
    } else if (std::strcmp(argv[1], "affine") == 0) {
        cpd::AffineResult result = cpd::affine(fixed, moving);
        cpd::Matrix transform = result.matrix();
        std::cout << transform << std::endl;
    } else if (std::strcmp(argv[1], "apply") == 0) {
        cpd::Matrix transform = cpd::matrix_from_path(argv[2]);
        cpd::Matrix points = cpd::matrix_from_path(argv[3]);
        points = cpd::apply_transformation_matrix(points, transform);
        std::ofstream outfile(argv[4]);
        outfile << points << std::endl;
        outfile.close();
    } else {
        std::cerr << "ERROR: invalid method '" << argv[1] << "'" << std::endl;
        return 1;
    }
    return 0;
}
