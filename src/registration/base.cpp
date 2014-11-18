#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


SpResult Base::operator()(arma::mat& X, arma::mat& Y) const
{
    Normalization normal = normalize(X, Y);
    SpResult result = execute(X, Y);
    denormalize(result, normal);
    return result;
}


Normalization Base::normalize(arma::mat& X, arma::mat& Y) const
{
    Normalization normal = {};
    return normal;
}


void Base::denormalize(SpResult& result, const Normalization& normal) const
{}


}
}
