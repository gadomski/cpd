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

/// \file
/// typedefs for matrices used in cpd.

#pragma once

#include <Eigen/Dense>

namespace cpd {

/// Typedef for our specific type of matrix.
typedef Eigen::MatrixXd Matrix;

/// Typedef for our specific type of vector.
typedef Eigen::VectorXd Vector;

/// Typedef for an index vector, used to index other matrices.
typedef Eigen::Matrix<Matrix::Index, Eigen::Dynamic, 1> IndexVector;

/// Typedef for our specific type of array.
typedef Eigen::ArrayXd Array;
}
