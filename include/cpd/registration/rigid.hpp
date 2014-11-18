#pragma once

#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


class Rigid : public Base
{
private:
    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const;

};


}
}
