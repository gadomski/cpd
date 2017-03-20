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

/// Create two random datasets and run cpd on them.
///
/// This is mostly to test for behavior when running overly-large data through
/// nonrigid (#104).

#include <iostream>
#include <string>

#include <cpd/nonrigid.hpp>
#include <cpd/rigid.hpp>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Invalid usage: cpd-random <method> <rows> <cols>"
                  << std::endl;
        return 1;
    }
    std::string method = argv[1];
    size_t rows = std::stoi(argv[2]);
    size_t cols = std::stoi(argv[3]);
    cpd::Matrix fixed = cpd::Matrix::Random(rows, cols);
    cpd::Matrix moving = cpd::Matrix::Random(rows, cols);

    if (method == "rigid") {
        cpd::rigid(fixed, moving);
    } else if (method == "nonrigid") {
        cpd::nonrigid(fixed, moving);
    } else {
        std::cout << "Invalid method: " << method << std::endl;
        return 1;
    }
    std::cout << "Registration completed OK" << std::endl;
    return 0;
}
