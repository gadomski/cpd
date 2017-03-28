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

#include <cpd/matrix.hpp>

namespace cpd {

Matrix apply_transformation_matrix(Matrix points, const Matrix& transform) {
    Matrix::Index rows = points.rows();
    Matrix::Index cols = points.cols() + 1;
    points.conservativeResize(rows, cols);
    points.col(cols - 1) = Vector::Ones(rows);
    Matrix transformed_points = points * transform.transpose();
    return transformed_points.leftCols(cols - 1);
}
} // namespace cpd
