#pragma once

#include <armadillo>

#include <cpd/registration/normalization.hpp>
#include <cpd/registration/result.hpp>


namespace cpd
{
namespace registration
{


class Base
{
public:

    explicit Base(double tol = 1e-5, int max_it = 150);

    SpResult operator()(arma::mat& X, arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(SpResult& result, const Normalization& normal) const;

    inline double get_tol() const { return m_tol; }
    inline int get_max_it() const { return m_max_it; }

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const = 0;

    double m_tol;
    int m_max_it;

};


}
}
