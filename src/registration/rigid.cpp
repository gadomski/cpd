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

    double L_old;
    arma::vec P1, Pt1;
    arma::mat PX;

    while (iter < get_max_it() &&
            ntol > get_tol() &&
            sigma2 > 10 * std::numeric_limits<double>::epsilon())
    {
        L_old = L;
        L = find_P(X, T, sigma2, get_outliers(), P1, Pt1, PX);

        break;
    }

    SpResult result(new Result());
    return result;
}


}
}
