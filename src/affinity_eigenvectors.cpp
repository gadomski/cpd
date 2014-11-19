#include <cpd/affinity_eigenvectors.hpp>

#include <cpd/affinity_matrix.hpp>


namespace cpd
{


void find_affinity_eigenvectors(const arma::mat& Y, double beta, int numeig, arma::mat& Q, arma::mat& S)
{
    const arma::uword M = Y.n_rows;
    const double h = std::sqrt(2) * beta;
    arma::mat G(M, M);
    construct_affinity_matrix(Y, Y, beta, G);

    arma::mat Qf;
    arma::vec s;
    arma::eig_sym(s, Qf, G);

    S.zeros(numeig, numeig);
    S.diag() = arma::flipud(s.subvec(M - numeig, M - 1));

    Q.zeros(numeig, numeig);
    Q = arma::fliplr(Qf.submat(0, M - numeig, M - 1, M - 1));
}


}
