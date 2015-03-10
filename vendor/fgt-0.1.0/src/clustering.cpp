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

#include "clustering.hpp"

#include "constant_series.hpp"
#include "monomials.hpp"
#include "nchoosek.hpp"
#include "p_max_total.hpp"
#include "truncation_number.hpp"


namespace fgt {


namespace {


double ddist(const arma::rowvec& x, const arma::rowvec& y) {
    return arma::accu(arma::pow(x - y, 2));
}
}


Clustering::Clustering(const arma::mat& source, arma::uword K, double bandwidth,
                       double epsilon)
    : m_source(source),
      m_K(K),
      m_indices(arma::zeros<arma::uvec>(source.n_rows)),
      m_centers(arma::zeros<arma::mat>(K, source.n_cols)),
      m_num_points(arma::zeros<arma::uvec>(K)),
      m_radii(K),
      m_rx(),
      m_bandwidth(bandwidth),
      m_epsilon(epsilon),
      m_p_max(0),
      m_constant_series() {}


Clustering::~Clustering() {}


void Clustering::cluster() {
    cluster_impl();
    double r =
        std::min(std::sqrt(get_dimensions()),
                 get_bandwidth() * std::sqrt(std::log(1 / get_epsilon())));
    double distance2 = get_rx() * get_rx();
    double cutoff_radius = get_rx() + r;
    m_p_max = choose_truncation_number(distance2, cutoff_radius,
                                       get_bandwidth(), get_epsilon());
    m_constant_series.resize(get_p_max_total(get_dimensions(), get_p_max()));
    compute_constant_series(m_source.n_cols, m_p_max, m_constant_series);
}


arma::mat Clustering::compute_C(const arma::vec& q, double cutoff_radius,
                                bool data_adaptive) const {
    double h2 = m_bandwidth * m_bandwidth;
    std::vector<arma::uword> truncation_numbers(m_source.n_rows);
    arma::uword p_max_actual = 0;
    arma::uword p_max = m_p_max;
    arma::uword p_max_total = get_p_max_total(get_dimensions(), p_max);
    arma::mat C = arma::zeros<arma::mat>(m_centers.n_rows, p_max_total);
    std::vector<double> monomials(C.n_cols);

    for (arma::uword i = 0; i < m_source.n_rows; ++i) {
        arma::uword k = m_indices(i);
        arma::rowvec dx = m_source.row(i) - m_centers.row(k);
        double distance2 = arma::accu(arma::pow(dx, 2));

        if (data_adaptive) {
            double cluster_cutoff_radius = cutoff_radius + get_radius(k);
            truncation_numbers[i] = choose_truncation_number(
                distance2, cluster_cutoff_radius, get_bandwidth(),
                get_epsilon(), get_p_max());
            if (truncation_numbers[i] > p_max_actual) {
                p_max_actual = truncation_numbers[i];
            }
            p_max = truncation_numbers[i];
            p_max_total = get_p_max_total(get_dimensions(), p_max);
        }
        compute_monomials(dx / m_bandwidth, p_max, monomials);
        double f = q(i) * std::exp(-distance2 / h2);
        for (arma::uword j = 0; j < p_max_total; ++j) {
            C(k, j) += f * monomials[j];
        }
    }

    if (data_adaptive) {
        C.resize(C.n_rows, get_p_max_total(get_dimensions(), p_max_actual));
    }

    for (arma::uword i = 0; i < C.n_rows; ++i) {
        for (arma::uword j = 0; j < C.n_cols; ++j) {
            C(i, j) = C(i, j) * m_constant_series[j];
        }
    }

    return C;
}


const optional_arma_uword_t GonzalezClustering::DefaultStartingIndex = {false,
                                                                        0};


GonzalezClustering::GonzalezClustering(const arma::mat& source, int K,
                                       double bandwidth, double epsilon,
                                       optional_arma_uword_t starting_index)
    : Clustering(source, K, bandwidth, epsilon),
      m_starting_index(starting_index) {}


void GonzalezClustering::cluster_impl() {
    arma::uword N = get_n_rows();
    arma::uword K = get_K();
    arma::uvec centers(K);
    arma::uvec cprev(N);
    arma::uvec cnext(N);
    arma::uvec far2c(K);
    arma::vec dist(N);

    arma::uword nc;
    if (m_starting_index.first) {
        nc = m_starting_index.second;
    } else {
        std::random_device rd;
        nc = rd() % N;
    }
    centers(0) = nc;

    for (arma::uword i = 0; i < N; ++i) {
        dist(i) =
            (i == nc) ? 0.0 : ddist(get_source_row(i), get_source_row(nc));
        cnext(i) = i + 1;
        cprev(i) = i - 1;
    }

    cnext(N - 1) = 0;
    cprev(0) = N - 1;

    nc = std::max_element(dist.begin(), dist.end()) - dist.begin();
    far2c(0) = nc;
    set_radius(0, dist(nc));

    for (int i = 1; i < K; ++i) {
        nc = far2c(get_radius_idxmax(i));

        centers(i) = nc;
        set_radius(i, 0.0);
        dist(nc) = 0.0;
        set_index(nc, i);
        far2c(i) = nc;

        cnext(cprev(nc)) = cnext(nc);
        cprev(cnext(nc)) = cprev(nc);
        cnext(nc) = nc;
        cprev(nc) = nc;

        for (int j = 0; j < i; ++j) {
            arma::uword ct_j = centers(j);
            double dc2cq = ddist(get_source_row(ct_j), get_source_row(nc)) / 4;
            if (dc2cq < get_radius(j)) {
                set_radius(j, 0.0);
                far2c(j) = ct_j;
                arma::uword k = cnext(ct_j);
                while (k != ct_j) {
                    arma::uword nextk = cnext(k);
                    double dist2c_k = dist(k);
                    if (dc2cq < dist2c_k) {
                        double dd =
                            ddist(get_source_row(k), get_source_row(nc));
                        if (dd < dist2c_k) {
                            dist(k) = dd;
                            set_index(k, i);
                            if (get_radius(i) < dd) {
                                set_radius(i, dd);
                                far2c(i) = k;
                            }
                            cnext(cprev(k)) = nextk;
                            cprev(nextk) = cprev(k);
                            cnext(k) = cnext(nc);
                            cprev(cnext(nc)) = k;
                            cnext(nc) = k;
                            cprev(k) = nc;
                        } else if (get_radius(j) < dist2c_k) {
                            set_radius(j, dist2c_k);
                            far2c(j) = k;
                        }
                    } else if (get_radius(j) < dist2c_k) {
                        set_radius(j, dist2c_k);
                        far2c(j) = k;
                    }
                    k = nextk;
                }
            }
        }
    }

    set_radii(arma::sqrt(get_radii()));
    set_rx(get_max_radius());

    arma::mat center_coordinates(get_centers());
    for (arma::uword i = 0; i < N; ++i) {
        increment_num_points(get_index(i));
        center_coordinates.row(get_index(i)) += get_source_row(i);
    }
    set_centers(center_coordinates /
                arma::repmat(get_num_points(), 1, get_dimensions()));
}
}
