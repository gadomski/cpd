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

#include <tuple>

#include <cpd/matrix.hpp>

namespace cpd {

/// Class for calculating P1, Pt1, PX, and L for each type of CPD.
class ProbabilityCalculator {
public:
    /// Creates a new probability calculator that will use FGT.
    ProbabilityCalculator(double outliers, double epsilon, double breakpoint);

    /// Calculates the probability matrices.
    std::tuple<Vector, Vector, Matrix, double>
    calculate(const MatrixRef source, const MatrixRef target, double sigma2);

private:
    double m_outliers;
    double m_epsilon;
    double m_breakpoint;
};
}
