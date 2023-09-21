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

#include <cpd/normalization.hpp>
#include <cpd/rigid.hpp>

namespace cpd {

template <typename M, typename V>
RigidResult<M, V> Rigid<M, V>::compute_one(
    const M& fixed, const M& moving, const Probabilities<M, V>& probabilities,
    typename M::Scalar sigma2) const {
    size_t cols = fixed.cols();
    typename M::Scalar np = probabilities.pt1.sum();
    V mu_x = fixed.transpose() * probabilities.pt1 / np;
    V mu_y = moving.transpose() * probabilities.p1 / np;
    M a = probabilities.px.transpose() * moving - np * mu_x * mu_y.transpose();
    Eigen::JacobiSVD<M, Eigen::NoQRPreconditioner> svd(
        a, Eigen::ComputeThinU | Eigen::ComputeThinV);
    M s = svd.singularValues().asDiagonal();
    M c = M::Identity(cols, cols);
    if (!m_reflections) {
        c(cols - 1, cols - 1) =
            (svd.matrixU() * svd.matrixV().transpose()).determinant();
    }
    RigidResult<M, V> result;
    result.rotation = svd.matrixU() * c * svd.matrixV().transpose();
    if (m_scale) {
        result.scale =
            (s * c).trace() / ((moving.array().pow(2) *
                                probabilities.p1.replicate(1, cols).array())
                                   .sum() -
                               np * mu_y.transpose() * mu_y);
        result.sigma2 = std::abs(((fixed.array().pow(2) *
                                   probabilities.pt1.replicate(1, cols).array())
                                      .sum()) -
                                 np * mu_x.transpose() * mu_x -
                                 result.scale * (s * c).trace()) /
                        (np * cols);
    } else {
        result.scale = 1.0;
        result.sigma2 =
            std::abs(((fixed.array().pow(2) *
                       probabilities.pt1.replicate(1, cols).array())
                          .sum() +
                      (moving.array().pow(2) *
                       probabilities.p1.replicate(1, cols).array())
                          .sum() -
                      np * mu_x.transpose() * mu_x -
                      np * mu_y.transpose() * mu_y - 2 * (s * c).trace())) /
            (np * cols);
    }
    result.translation = mu_x - result.scale * result.rotation * mu_y;
    result.points = result.scale * moving * result.rotation.transpose() +
                    result.translation.transpose().replicate(moving.rows(), 1);
    return result;
}

template <typename M, typename V>
RigidResult<M, V> rigid(const M& fixed, const M& moving) {
    Rigid<M, V> rigid;
    return rigid.run(fixed, moving);
}

template <typename M, typename V>
M RigidResult<M, V>::matrix() const {
    typename M::Index rows = rotation.rows() + 1;
    typename M::Index cols = rotation.cols() + 1;
    M matrix = M::Zero(rows, cols);
    for (typename M::Index row = 0; row < rotation.rows(); ++row) {
        for (typename M::Index col = 0; col < rotation.cols(); ++col) {
            matrix(row, col) = rotation(row, col) * scale;
        }
        matrix(row, cols - 1) = translation(row);
    }
    matrix(rows - 1, cols - 1) = 1;
    return matrix;
}

template <typename M, typename V>
void RigidResult<M, V>::denormalize(const Normalization<M, V>& normalization) {
    Result<M, V>::denormalize(normalization);
    scale = scale * normalization.fixed_scale / normalization.moving_scale;
    translation = normalization.fixed_scale * translation +
                  normalization.fixed_mean -
                  scale * rotation * normalization.moving_mean;
}

template class Rigid<Matrix, Vector>;
template class RigidResult<Matrix, Vector>;
template RigidResult<Matrix, Vector> rigid(const Matrix& fixed,
                                           const Matrix& moving);

template class Rigid<MatrixF, VectorF>;
template class RigidResult<MatrixF, VectorF>;
template RigidResult<MatrixF, VectorF> rigid(const MatrixF& fixed,
                                             const MatrixF& moving);

} // namespace cpd
