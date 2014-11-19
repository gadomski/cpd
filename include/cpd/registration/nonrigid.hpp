#pragma once

#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


class Nonrigid : public Base
{
public:

    explicit Nonrigid(
            double tol = 1e-5,
            int max_it = 150,
            double outliers = 0.1,
            bool use_fgt = false,
            double beta = 2,
            double lambda =  3
            );

    inline double get_beta() const { return m_beta; }
    inline double get_lambda() const { return m_lambda; }

private:

    virtual SpResult execute(const arma::mat& X, arma::mat& Y) const;

    double m_beta;
    double m_lambda;
};


}
}
