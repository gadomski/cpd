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

#include <fstream>
#include <vector>

#include "cpd/matrix.hpp"
#include "cpd/utils.hpp"

namespace cpd {

template <typename M>
M matrix_from_path(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::stringstream msg;
        msg << "Unable to open file for reading: " << path;
        throw std::runtime_error(msg.str());
    }
    std::string line;
    std::vector<std::vector<typename M::Scalar>> rows;
    while (std::getline(file, line)) {
        std::vector<typename M::Scalar> row;
        std::stringstream ss(line);
        typename M::Scalar n;
        while (ss >> n) {
            row.push_back(n);
            // TODO support other delimiters than commas
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        if (!rows.empty() && rows.back().size() != row.size()) {
            std::stringstream msg;
            msg << "Irregular number of rows: " << rows.back().size() << ", "
                << row.size();
            throw std::runtime_error(msg.str());
        }
        rows.push_back(row);
    }
    if (rows.empty()) {
        return M(0, 0);
    }
    size_t nrows = rows.size();
    size_t ncols = rows[0].size();
    M matrix(nrows, ncols);
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            matrix(i, j) = rows[i][j];
        }
    }
    return matrix;
}

template <typename M>
typename M::Scalar default_sigma2(const M& fixed, const M& moving) {
    return ((moving.rows() * (fixed.transpose() * fixed).trace()) +
            (fixed.rows() * (moving.transpose() * moving).trace()) -
            2 * fixed.colwise().sum() * moving.colwise().sum().transpose()) /
           (fixed.rows() * moving.rows() * fixed.cols());
}

template <typename M>
M affinity(const M& x, const M& y, typename M::Scalar beta) {
    typename M::Scalar k = -2.0 * beta * beta;
    size_t x_rows = x.rows();
    size_t y_rows = y.rows();
    M g;
    try {
        g = M(x_rows, y_rows);
    } catch (const std::bad_alloc& err) {
        std::stringstream msg;
        msg << "Unable to allocate " << x_rows << " by " << y_rows
            << " affinity matrix, try again with fewer points";
        throw std::runtime_error(msg.str());
    }
    for (size_t i = 0; i < y_rows; ++i) {
        g.col(i) = ((x.array() - y.row(i).replicate(x_rows, 1).array())
                        .pow(2)
                        .rowwise()
                        .sum() /
                    k)
                       .exp();
    }
    return g;
}
template Matrix matrix_from_path(const std::string& path);
template Matrix affinity(const Matrix& x, const Matrix& y, Matrix::Scalar beta);
template Matrix::Scalar default_sigma2(const Matrix& fixed,
                                       const Matrix& moving);

template MatrixF matrix_from_path(const std::string& path);
template MatrixF affinity(const MatrixF& x, const MatrixF& y,
                          MatrixF::Scalar beta);
template MatrixF::Scalar default_sigma2(const MatrixF& fixed,
                                        const MatrixF& moving);

} // namespace cpd
