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

#include "clustering.hpp"
#include "monomials.hpp"
#include "nchoosek.hpp"
#include "p_max_total.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>


namespace fgt {

Ifgt::Parameters Ifgt::choose_parameters(arma::uword d, double bandwidth,
                                         double epsilon) {
    return choose_parameters(
        d, bandwidth, epsilon,
        std::round(NumClusterLimitFactor * std::sqrt(d) / bandwidth));
}


Ifgt::Parameters Ifgt::choose_parameters(arma::uword d, double bandwidth,
                                         double epsilon, arma::uword k_limit) {
    Parameters params;
    double R = std::sqrt(d);
    double h2 = bandwidth * bandwidth;
    double complexity_min = std::numeric_limits<double>::max();
    double rx = 0.0;
    double error_min = epsilon + 1;

    params.radius = std::min(R, bandwidth * std::sqrt(std::log(1 / epsilon)));
    params.num_clusters = 0;

    for (arma::uword i = 0; i < k_limit; ++i) {
        rx = std::pow(double(i + 1), -1.0 / double(d));
        double rx2 = rx * rx;
        double n =
            std::min(double(i + 1), std::pow(params.radius / rx, double(d)));
        double error = 1;
        double temp = 1;
        arma::uword p = 0;

        while ((error > epsilon) and (p <= MaxNumClusters)) {
            ++p;
            double b = std::min((rx + std::sqrt(rx2 + 2 * p * h2)) / 2,
                                rx + params.radius);
            double c = rx - b;
            temp *= 2 * rx * b / h2 / p;
            error = temp * std::exp(-c * c / h2);
        }
        double complexity =
            i + 1 + std::log(double(i + 1)) + (n + 1) * nchoosek(p - 1 + d, d);

        if (complexity < complexity_min) {
            complexity_min = complexity;
            params.num_clusters = i + 1;
            error_min = error;
        }
    }

    if (error_min > epsilon) {
        params.num_clusters = k_limit;
    }

    return params;
}


Ifgt::Ifgt(const arma::mat& source, double bandwidth, double epsilon,
           int k_limit)
    : GaussTransform(source, bandwidth),
      m_epsilon(epsilon),
      m_k_limit(k_limit),
      m_clustering_starting_index(std::make_pair(false, 0)),
      m_data_adaptive(false) {}


optional_arma_uword_t Ifgt::get_clustering_starting_index() const {
    return m_clustering_starting_index;
}


Ifgt& Ifgt::set_clustering_starting_index(arma::uword index) {
    m_clustering_starting_index = std::make_pair(true, index);
    return *this;
}


Ifgt& Ifgt::use_data_adaptive_truncation(bool data_adaptive) {
    m_data_adaptive = data_adaptive;
    return *this;
}


arma::vec Ifgt::compute_impl(const arma::mat& target,
                             const arma::vec& weights) const {
    const arma::mat& source = get_source();
    double bandwidth = get_bandwidth();

    Parameters params = choose_parameters(source.n_cols, bandwidth, m_epsilon);

    GonzalezClustering clustering(source, params.num_clusters, bandwidth,
                                  m_epsilon, get_clustering_starting_index());
    clustering.cluster();

    arma::uword p_max = clustering.get_p_max();
    arma::uword p_max_total = get_p_max_total(source.n_cols, p_max);
    std::vector<double> monomials(p_max_total);
    std::vector<double> dy(source.n_cols);
    std::vector<double> dy_scaled(source.n_cols);
    arma::vec G(target.n_rows);
    double h2 = bandwidth * bandwidth;
    arma::vec ry2 = arma::pow(params.radius + clustering.get_radii(), 2);

    arma::mat C = clustering.compute_C(weights, params.radius, m_data_adaptive);

    for (arma::uword j = 0; j < target.n_rows; ++j) {
        G(j) = 0.0;
        for (arma::uword k = 0; k < params.num_clusters; ++k) {
            double distance2 = 0;
            for (size_t i = 0; i < source.n_cols; ++i) {
                dy[i] = target(j, i) - clustering.get_centers()(k, i);
                dy_scaled[i] = dy[i] / bandwidth;
                distance2 += dy[i] * dy[i];
            }
            if (distance2 <= ry2(k)) {
                double g = std::exp(-distance2 / h2);
                compute_monomials(dy_scaled, p_max, monomials);
                for (arma::uword i = 0; i < C.n_cols; ++i) {
                    G(j) += C(k, i) * monomials[i] * g;
                }
            }
        }
    }
    return G;
}
}
