#include <cpd/affinity_matrix.hpp>


namespace cpd
{


void construct_affinity_matrix(const arma::mat& X, const arma::mat& Y, double beta, arma::mat& G)
{
    double k = -2 * std::pow(beta, 2);
    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    G.set_size(N, M);

    for (arma::uword i = 0; i < M; ++i)
    {
        G.col(i) = arma::exp(arma::sum(arma::pow(X - arma::repmat(Y.row(i), N, 1), 2), 1) / k);
    }

}


}
