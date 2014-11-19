#include <cpd/registration/nonrigid_lowrank.hpp>

#include <cpd/affinity_eigenvectors.hpp>
#include <cpd/sigma2.hpp>
#include <cpd/spdiag_locations.hpp>


namespace cpd
{
namespace registration
{


NonrigidLowrank::NonrigidLowrank(double tol, int max_it, double outliers, bool use_fgt,
                                 double beta, double lambda, int numeig)
    : Nonrigid(tol, max_it, outliers, use_fgt, beta, lambda)
    , m_numeig(numeig)
{}



SpResult NonrigidLowrank::execute(const arma::mat& X, const arma::mat& Y) const
{
    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;
    const arma::uword D = Y.n_cols;

    double sigma2 = get_sigma2(X, Y);
    const double sigma2_init = sigma2;

    arma::mat T = Y;
    arma::mat W = arma::zeros<arma::mat>(M, D);
    
    int iter = 0;
    double ntol = get_tol() + 10;
    double L = 0;

    arma::mat Q, S;
    find_affinity_eigenvectors(Y, get_beta(), get_numeig(), Q, S);

    arma::sp_mat invS(spdiag_locations(get_numeig()), 1 / S.diag());

    double L_old, Np;
    arma::vec P1(M), Pt1(M);
    arma::mat PX(M, D);

    while (iter < get_max_it() &&
            ntol > get_tol() &&
            sigma2 > 10 * std::numeric_limits<double>::epsilon())
    {
        L_old = L;
        arma::mat QtW = Q.t() * W;

        L = find_P(X, T, sigma2, P1, Pt1, PX);

        L = L + get_lambda() / 2 * arma::trace(QtW.t() * S * QtW);
        ntol = std::abs((L - L_old) / L);

        // TODO logging
        //std::cerr << "dL= " << ntol << ", iter= " << iter << ", sigma2= " << sigma2 << std::endl;

        arma::sp_mat dP(spdiag_locations(M), P1);
        arma::mat dPQ = dP * Q;
        arma::mat F = PX - dP * Y;

        W = 1 / (get_lambda() * sigma2) *
            (F - dPQ * (arma::solve(get_lambda() * sigma2 * invS + Q.t() * dPQ, Q.t() * F)));

        T = Y + (Q * (S * (Q.t() * W)));

        Np = arma::sum(P1);
        sigma2 = std::abs(
                arma::accu(arma::pow(X, 2) % arma::repmat(Pt1, 1, D)) +
                arma::accu(arma::pow(T, 2) % arma::repmat(P1, 1, D)) -
                2 * arma::trace(PX.t() * T)) /
            (Np * D);

        ++iter;
    }

    SpResult result(new Result());
    result->Y = T;
    return result;
}


}
}
