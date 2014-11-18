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

    explicit Base(
            float tol = 1e-5,
            int max_it = 150,
            float outliers = 0.1
            );

    SpResult operator()(arma::mat& X, arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(SpResult& result, const Normalization& normal) const;

    double find_P(
            const arma::mat& X,
            const arma::mat& Y,
            double sigma2,
            float outliers,
            arma::vec& P1,
            arma::vec& Pt1,
            arma::mat& PX
            ) const;

    inline float get_tol() const { return m_tol; }
    inline int get_max_it() const { return m_max_it; }
    inline float get_outliers() const { return m_outliers; }

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const = 0;


    float m_tol;
    int m_max_it;
    float m_outliers;

};


}
}
