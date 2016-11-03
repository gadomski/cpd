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

#include "affinity_matrix.hpp"

namespace cpd {

Matrix affinity_matrix(const Matrix& x, const Matrix& y, double beta) {
    double k = -2.0 * beta * beta;
    size_t x_rows = x.rows();
    size_t y_rows = y.rows();
    Matrix g(x_rows, y_rows);
    for (size_t i = 0; i < y_rows; ++i) {
        g.col(i) = ((x.array() - y.row(i).replicate(x_rows, 1).array())
                        .pow(2)
                        .rowwise()
                        .sum() /
                    k).exp();
    }
    return g;
}
}
