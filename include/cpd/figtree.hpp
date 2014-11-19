#include <armadillo>

#include <figtree.h>


namespace cpd
{


// Assume that the input matrices have already been tranposed so
// callers can re-use transposed matrices.
inline void figtree_wrap(arma::mat& Xt, arma::mat& Yt, arma::vec& q,
                         double h, double epsilon, arma::vec& out, int eval_method = FIGTREE_EVAL_AUTO)
{
    const arma::uword N = Xt.n_cols;
    const arma::uword M = Yt.n_cols;
    const arma::uword D = Yt.n_rows;
    const int W = 1;

    figtree(D, N, M, W, Xt.memptr(), h, q.memptr(), Yt.memptr(), epsilon,
            out.memptr(), eval_method);
}


}
