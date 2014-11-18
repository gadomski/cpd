#pragma once

#include <armadillo>

#include <cpd/registration/result.hpp>


namespace cpd
{
namespace registration
{


class Base
{
public:

    SpResult operator()(arma::mat& X, arma::mat& Y) const;
};


}
}
