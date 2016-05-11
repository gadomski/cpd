// cpd - Coherent Point Drift
// Copyright (C) 2016 Pete Gadomski <pete.gadomski@gmail.com>
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

#include <fstream>
#include <vector>

#include <cpd/matrix.hpp>

namespace cpd {

Matrix matrix_from_path(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::stringstream ss;
        ss << "Could not open file: " << path;
        throw std::runtime_error(ss.str());
    }
    std::vector<double> data;
    size_t rows = 0;
    size_t cols = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        size_t nvalues = 0;
        double value;
        while (ss >> value) {
            data.push_back(value);
            ++nvalues;
        }
        if (cols == 0) {
            cols = nvalues;
        } else if (cols != nvalues) {
            std::stringstream ss;
            ss << "Dimension mismatch";
            throw std::runtime_error(ss.str());
        }
        ++rows;
    }
    Matrix matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = data[i * cols + j];
        }
    }
    return matrix;
}
}
