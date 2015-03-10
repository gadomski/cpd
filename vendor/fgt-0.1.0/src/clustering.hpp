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

#include <fgt/typedefs.hpp>

#include <armadillo>


namespace fgt {


class Clustering {
public:
    Clustering(const arma::mat& source, arma::uword K, double bandwidth,
               double epsilon);
    virtual ~Clustering();

    void cluster();
    arma::mat compute_C(const arma::vec& q, double cutoff_radius,
                        bool data_adaptive) const;
    double get_bandwidth() const { return m_bandwidth; }
    const arma::mat& get_centers() const { return m_centers; }
    arma::uword get_dimensions() const { return m_source.n_cols; }
    double get_epsilon() const { return m_epsilon; }
    arma::uword get_index(arma::uword i) const { return m_indices(i); }
    const arma::uvec& get_indices() const { return m_indices; }
    arma::uword get_K() const { return m_K; }
    double get_max_radius() const {
        return *std::max_element(m_radii.begin(), m_radii.end());
    }
    const arma::uword get_n_rows() const { return m_source.n_rows; }
    const arma::uvec& get_num_points() const { return m_num_points; }
    arma::uword get_p_max() const { return m_p_max; }
    const arma::vec& get_radii() const { return m_radii; }
    double get_radius(arma::uword i) const { return m_radii(i); }
    arma::uword get_radius_idxmax(arma::uword i) const {
        return std::max_element(m_radii.begin(), m_radii.begin() + i) -
               m_radii.begin();
    }
    double get_rx() const { return m_rx; }
    arma::rowvec get_source_row(arma::uword i) const { return m_source.row(i); }
    void increment_num_points(arma::uword i) { ++m_num_points(i); }
    void set_index(arma::uword i, arma::uword index) { m_indices(i) = index; }
    void set_radius(arma::uword i, double r) { m_radii(i) = r; }
    void set_radii(arma::vec radii) { m_radii = radii; }
    void set_rx(double rx) { m_rx = rx; }
    void set_centers(const arma::mat& centers) { m_centers = centers; }

private:
    virtual void cluster_impl() = 0;

    const arma::mat& m_source;
    arma::uword m_K;
    arma::uvec m_indices;
    arma::mat m_centers;
    arma::uvec m_num_points;
    arma::vec m_radii;
    double m_rx;
    double m_bandwidth;
    double m_epsilon;
    arma::uword m_p_max;
    std::vector<double> m_constant_series;
};


class GonzalezClustering : public Clustering {
public:
    static const optional_arma_uword_t DefaultStartingIndex;

    GonzalezClustering(
        const arma::mat& source, int K, double bandwidth, double epsilon,
        optional_arma_uword_t starting_index = DefaultStartingIndex);

private:
    virtual void cluster_impl() override;

    optional_arma_uword_t m_starting_index;
};
}
