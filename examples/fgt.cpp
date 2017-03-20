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

#include <cpd/gauss_transform_fgt.hpp>
#include <cpd/jsoncpp.hpp>
#include <cpd/rigid.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "ERROR: invalid usage" << std::endl;
        std::cout << "USAGE: cpd-fgt <fixed> <moving>" << std::endl;
        return 1;
    }
    cpd::Matrix fixed = cpd::matrix_from_path(argv[1]);
    cpd::Matrix moving = cpd::matrix_from_path(argv[2]);
    cpd::Rigid rigid;
    rigid.gauss_transform(std::move(
        std::unique_ptr<cpd::GaussTransform>(new cpd::GaussTransformFgt())));
    cpd::RigidResult result = rigid.run(fixed, moving);
    std::cout << cpd::to_json(result) << std::endl;
    return 0;
}
