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

/// \file
///
/// The always-present, always-ambiguous utils file.

#pragma once

#include <cpd/matrix.hpp>

namespace cpd {

/// Loads a matrix from a delimited text file.
template <typename M>
M matrix_from_path(const std::string& path);

/// Computes the default sigma2 for the given matrices.
template <typename M>
typename M::Scalar default_sigma2(const M& fixed, const M& moving);

// typedef decltype(m1*m2)::Scalar ResScalar;

/// Computes the affinity matrix between the two matrices.
template <typename M>
M affinity(const M& fixed, const M& moving, typename M::Scalar beta);
} // namespace cpd
