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

#define _USE_MATH_DEFINES

#include <cmath>
#include <cpd/gauss_transform.hpp>

namespace cpd {
template <typename M, typename V>
Probabilities<M, V> GaussTransformDirect<M, V>::compute(
    const M& fixed, const M& moving, typename M::Scalar sigma2,
    typename M::Scalar outliers) const {
    typename M::Scalar ksig = -2.0 * sigma2;
    size_t cols = fixed.cols();
    typename M::Scalar outlier_tmp =
        (outliers * moving.rows() * std::pow(-ksig * M_PI, 0.5 * cols)) /
        ((1 - outliers) * fixed.rows());
    V p = V::Zero(moving.rows());
    V p1 = V::Zero(moving.rows());
    V p1_max = V::Zero(moving.rows());
    V pt1 = V::Zero(fixed.rows());
    M px = M::Zero(moving.rows(), cols);
    IndexVector correspondence = IndexVector::Zero(moving.rows());
    typename M::Scalar l = 0.0;

    for (typename M::Index i = 0; i < fixed.rows(); ++i) {
        typename M::Scalar sp = 0;
        for (typename M::Index j = 0; j < moving.rows(); ++j) {
            typename M::Scalar razn =
                (fixed.row(i) - moving.row(j)).array().pow(2).sum();
            p(j) = std::exp(razn / ksig);
            sp += p(j);
        }
        sp += outlier_tmp;
        pt1(i) = 1 - outlier_tmp / sp;
        for (typename M::Index j = 0; j < moving.rows(); ++j) {
            p1(j) += p(j) / sp;
            px.row(j) += fixed.row(i) * p(j) / sp;
            if (p(j) / sp > p1_max(j)) {
                correspondence(j) = i;
                p1_max(j) = p(j) / sp;
            }
        }
        l += -std::log(sp);
    }
    l += cols * fixed.rows() * std::log(sigma2) / 2;
    return { p1, pt1, px, l, correspondence };
}
template struct Probabilities<Matrix, Vector>;
template class GaussTransform<Matrix, Vector>;
template class GaussTransformDirect<Matrix, Vector>;
std::unique_ptr<GaussTransform<Matrix, Vector>> dummy;

template struct Probabilities<MatrixF, VectorF>;
template class GaussTransform<MatrixF, VectorF>;
template class GaussTransformDirect<MatrixF, VectorF>;
std::unique_ptr<GaussTransform<MatrixF, VectorF>> dummyF;

} // namespace cpd
