#include <cpd/sigma2.hpp>


namespace cpd
{


double get_sigma2(const arma::mat& X, const arma::mat& Y)
{
    return (Y.n_rows * trace(X.t() * X) +
            X.n_rows * trace(Y.t() * Y) -
            arma::as_scalar(2 * sum(X) * sum(Y).t())) /
        (Y.n_rows * X.n_rows * Y.n_cols);
}


}
