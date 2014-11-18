#include <cpd/registration/rigid.hpp>

#include <cpd/sigma2.hpp>


namespace cpd
{
namespace registration
{

SpResult Rigid::execute(const arma::mat& X, const arma::mat& Y) const
{
    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    double sigma2 = get_sigma2(X, Y);
    const double sigma2_init = sigma2;

    arma::mat T = Y;
    double s = 1;
    arma::mat R = arma::eye<arma::mat>(D, D);

    int iter = 0;
    double ntol = get_tol() + 10;
    double L = 0;

    SpResult result(new Result());
    return result;
}


}
}
