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

    SpResult operator()(arma::mat& X, arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(SpResult& result, const Normalization& normal) const;

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const = 0;

};


}
}
