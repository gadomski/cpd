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

#include "armadillo_adapter.hpp"

#include <armadillo>
#include <nanoflann.hpp>

#include <cmath>
#include <sstream>
#include <utility>
#include <vector>


namespace fgt {


DirectTree::DirectTree(const arma::mat& source, double bandwidth,
                       double epsilon)
    : GaussTransform(source, bandwidth),
      m_epsilon(epsilon),
      m_max_leaf(MaxLeafSize) {}


arma::vec DirectTree::compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const {
    double bandwidth2 = get_bandwidth() * get_bandwidth();
    double cutoff_radius = get_bandwidth() * std::sqrt(std::log(1 / m_epsilon));
    double cutoff_radius2 = cutoff_radius * cutoff_radius;
    arma::vec g = arma::zeros<arma::vec>(target.n_rows);
    typedef nanoflann::KDTreeSingleIndexAdaptor<
        L2_Simple_ArmadilloAdaptor, ArmadilloAdaptor, -1, arma::uword> tree_t;
    ArmadilloAdaptor adapter(get_source());
    tree_t tree(get_dimensions(), adapter,
                nanoflann::KDTreeSingleIndexAdaptorParams(m_max_leaf));
    tree.buildIndex();

    std::vector<double> point(get_dimensions());
    std::vector<std::pair<arma::uword, double>> indices_distances;
    indices_distances.reserve(get_source_n_rows());
    nanoflann::SearchParams search_params;
    search_params.sorted = false;
    for (int j = 0; j < target.n_rows; ++j) {
        point =
            std::move(arma::conv_to<std::vector<double>>::from(target.row(j)));
        size_t num_points_found = tree.radiusSearch(
            point.data(), cutoff_radius2, indices_distances, search_params);
        for (size_t i = 0; i < num_points_found; ++i) {
            auto entry = indices_distances[i];
            g(j) += weights(entry.first) * std::exp(-entry.second / bandwidth2);
        }
    }
    return g;
}
}
