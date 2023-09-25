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

template <typename M, typename V>
M apply_transformation_matrix(M points, const M& transform) {
    typename M::Index rows = points.rows();
    typename M::Index cols = points.cols() + 1;
    points.conservativeResize(rows, cols);
    points.col(cols - 1) = V::Ones(rows);
    M transformed_points = points * transform.transpose();
    return transformed_points.leftCols(cols - 1);
}
template Matrix apply_transformation_matrix<Matrix, Vector>(
    Matrix points, const Matrix& transform);
/*
template MatrixF apply_transformation_matrix<MatrixF, VectorF>(
  MatrixF points, const MatrixF& transform);
*/
} // namespace cpd
