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

#include <memory>


namespace fgt {


class GaussTransform {
public:
    GaussTransform(const arma::mat& source, double bandwidth);
    virtual ~GaussTransform();

    arma::vec compute(const arma::mat& target) const;
    arma::vec compute(const arma::mat& target, const arma::vec& weights) const;
    double get_bandwidth() const { return m_bandwidth; }
    arma::uword get_dimensions() const { return m_source.n_cols; }
    const arma::mat& get_source() const { return m_source; }
    arma::uword get_source_n_rows() const { return m_source.n_rows; }

private:
    virtual arma::vec compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const = 0;

    const arma::mat& m_source;
    double m_bandwidth;
};


class Direct : public GaussTransform {
public:
    using GaussTransform::GaussTransform;

private:
    virtual arma::vec compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const override;
};


class DirectTree : public GaussTransform {
public:
    static const size_t MaxLeafSize = 10;

    DirectTree(const arma::mat& source, double bandwidth, double epsilon);

private:
    virtual arma::vec compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const override;

    double m_epsilon;
    size_t m_max_leaf;
};


class Ifgt : public GaussTransform {
public:
    struct Parameters {
        arma::uword num_clusters;
        double radius;
    };

    static const arma::uword DefaultNumClustersLimit = 50;
    static const arma::uword MaxNumClusters = 200;
    static const arma::uword NumClusterLimitFactor = 20;
    static const bool DefaultUseDataAdaptive = false;

    Ifgt(const arma::mat& source, double bandwidth, double epsilon,
         int k_limit = DefaultNumClustersLimit);

    static Parameters choose_parameters(arma::uword dimensions,
                                        double bandwidth, double epsilon);
    static Parameters choose_parameters(arma::uword dimensions,
                                        double bandwidth, double epsilon,
                                        arma::uword k_limit);

    optional_arma_uword_t get_clustering_starting_index() const;
    Ifgt& set_clustering_starting_index(arma::uword index);
    Ifgt& use_data_adaptive_truncation(bool data_adaptive);

private:
    virtual arma::vec compute_impl(const arma::mat& target,
                                   const arma::vec& weights) const override;

    double m_epsilon;
    int m_k_limit;
    optional_arma_uword_t m_clustering_starting_index;
    bool m_data_adaptive;
};


typedef std::unique_ptr<GaussTransform> GaussTransformUnqPtr;

GaussTransformUnqPtr choose_gaussian_transform(const arma::mat& source,
                                               double bandwidth,
                                               double epsilon);
}
