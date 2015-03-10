// fgt, C++ library for Fast Gauss Transforms
// Copyright (C) 2015 Peter J. Gadomski <pete.gadomski@gmail.com>
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

#include <fgt/fgt.hpp>

#include <fgt/exceptions.hpp>


namespace fgt {


GaussTransform::GaussTransform(const arma::mat& source, double bandwidth)
    : m_source(source), m_bandwidth(bandwidth) {}


GaussTransform::~GaussTransform() {}


arma::vec GaussTransform::compute(const arma::mat& target) const {
    return compute(target, arma::ones<arma::vec>(get_source_n_rows()));
}

arma::vec GaussTransform::compute(const arma::mat& target,
                                  const arma::vec& weights) const {
    if (m_source.n_cols != target.n_cols) {
        std::stringstream ss;
        ss << "Dimentionality of source and target do not match ("
           << m_source.n_cols << " vs " << target.n_cols << ")";
        throw dimension_mismatch(ss.str());
    }
    if (m_source.n_rows != weights.n_rows) {
        std::stringstream ss;
        ss << "Source and weights do not have the same number of rows ("
           << m_source.n_rows << " vs " << weights.n_rows << ")";
        throw dimension_mismatch(ss.str());
    }
    return compute_impl(target, weights);
}
}
