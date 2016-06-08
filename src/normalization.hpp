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

#pragma once

#include <cpd/matrix.hpp>

namespace cpd {
class Normalization {
public:
    Normalization(const MatrixRef fixed, const MatrixRef moving);

    const Matrix& fixed() const { return m_fixed; }
    const Matrix& moving() const { return m_moving; }
    const RowVector& translation_x() const { return m_translation_x; }
    const RowVector& translation_y() const { return m_translation_y; }
    double scaling() const { return m_scaling; }

    template <typename T>
    T denormalize(const T& result) const {
        T out(result);
        out.points = result.points * m_scaling +
                     m_translation_x.replicate(result.points.rows(), 1);
        return out;
    }

private:
    Matrix m_fixed;
    Matrix m_moving;
    RowVector m_translation_x;
    RowVector m_translation_y;
    double m_scaling;
};
}
