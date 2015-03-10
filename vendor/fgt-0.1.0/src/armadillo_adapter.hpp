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

#pragma once

#include <armadillo>
#include <nanoflann.hpp>


namespace fgt {


class ArmadilloAdaptor {
public:
    ArmadilloAdaptor(const arma::mat& data) : m_data(data) {}

    const arma::mat& derived() const { return m_data; };
    arma::uword kdtree_get_point_count() const { return m_data.n_rows; }
    double kdtree_distance(const double* p1, const arma::uword idx_p2,
                           size_t size) const {
        return arma::accu(
            arma::pow(m_data.row(idx_p2) - arma::rowvec(p1, size), 2));
    }
    double kdtree_get_pt(const arma::uword idx, int dim) const {
        return m_data(idx, dim);
    }
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& bounding_box) const {
        return false;
    }

private:
    const arma::mat& m_data;
};


typedef nanoflann::L2_Simple_Adaptor<double, ArmadilloAdaptor>
    L2_Simple_ArmadilloAdaptor;
}
