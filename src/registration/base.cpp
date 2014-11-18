#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


SpResult Base::operator()(arma::mat& X, arma::mat& Y) const
{
    SpResult result(new Result());
    return result;
}


}
}
