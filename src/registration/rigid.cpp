#include <cpd/registration/rigid.hpp>

#include <cpd/sigma2.hpp>


namespace cpd
{
namespace registration
{

SpResult Rigid::execute(const arma::mat& X, const arma::mat& Y) const
{
    arma::uword N = X.n_rows;
    arma::uword M = Y.n_rows;
    arma::uword D = Y.n_cols;

    double sigma2 = get_sigma2(X, Y);

    SpResult result(new Result());
    return result;
}


}
}
