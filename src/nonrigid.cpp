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

#include <cpd/nonrigid.hpp>

namespace cpd {

template <typename M, typename V>
void Nonrigid<M, V>::init(const M& fixed, const M& moving) {
    m_g = affinity(moving, moving, m_beta);
    m_w = M::Zero(moving.rows(), moving.cols());
}

template <typename M, typename V>
void Nonrigid<M, V>::modify_probabilities(
    Probabilities<M, V>& probabilities) const {
    probabilities.l += m_lambda / 2.0 * (m_w.transpose() * m_g * m_w).trace();
}

template <typename M, typename V>
NonrigidResult<M, V> Nonrigid<M, V>::compute_one(
    const M& fixed, const M& moving, const Probabilities<M, V>& probabilities,
    typename M::Scalar sigma2) const {
    size_t cols = fixed.cols();
    auto dp = probabilities.p1.asDiagonal();
    M w = (dp * m_g +
           m_lambda * sigma2 * M::Identity(moving.rows(), moving.rows()))
              .colPivHouseholderQr()
              .solve(probabilities.px - dp * moving);
    NonrigidResult<M, V> result;
    result.points = moving + m_g * w;
    typename M::Scalar np = probabilities.p1.sum();
    result.sigma2 = std::abs(
        ((fixed.array().pow(2) * probabilities.pt1.replicate(1, cols).array())
             .sum() +
         (result.points.array().pow(2) *
          probabilities.p1.replicate(1, cols).array())
             .sum() -
         2 * (probabilities.px.transpose() * result.points).trace()) /
        (np * cols));
    return result;
}

template <typename M, typename V>
NonrigidResult<M, V> nonrigid(const M& fixed, const M& moving) {
    Nonrigid<M, V> nonrigid;
    return nonrigid.run(fixed, moving);
}
template class Nonrigid<Matrix, Vector>;
template class NonrigidResult<Matrix, Vector>;
template NonrigidResult<Matrix, Vector> nonrigid(const Matrix& fixed,
                                                 const Matrix& moving);
template class Nonrigid<MatrixF, VectorF>;
template class NonrigidResult<MatrixF, VectorF>;
template NonrigidResult<MatrixF, VectorF> nonrigid(const MatrixF& fixed,
                                                   const MatrixF& moving);
} // namespace cpd
