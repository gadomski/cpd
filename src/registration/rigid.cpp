#include <cpd/registration/rigid.hpp>

#include <cpd/sigma2.hpp>


namespace cpd
{
namespace registration
{


Rigid::Rigid(float tol, int max_it, float outliers, bool use_fgt, bool strict_rot,
             bool use_scaling)
    : Base(tol, max_it, outliers, use_fgt)
    , m_strict_rot(strict_rot)
    , m_use_scaling(use_scaling)
{}


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

    double L_old, Np;
    arma::vec P1(M), Pt1(M), mu_x(D), mu_y(D);
    arma::mat PX(M, D), A(D, D);

    while (iter < get_max_it() &&
            ntol > get_tol() &&
            sigma2 > 10 * std::numeric_limits<double>::epsilon())
    {
        L_old = L;
        L = find_P(X, T, sigma2, get_outliers(), P1, Pt1, PX);

        ntol = std::abs((L - L_old) / L);

        // TODO logging
        
        Np = arma::sum(Pt1);
        mu_x = X.t() * Pt1 / Np;
        mu_y = Y.t() * P1 / Np;

        A = PX.t() * Y - Np * (mu_x * mu_y.t());

        arma::mat U(D, D), V(D, D);
        arma::mat C = arma::eye<arma::mat>(D, D);
        arma::vec sv;
        arma::svd(U, sv, V, A);
        arma::mat S = arma::diagmat(sv);

        if (strict_rot())
        {
            C(D - 1, D - 1) = arma::det(U * V.t());
        }

        R = U * C * V.t();

        if (use_scaling())
        {
             
        }
        else
        {

        }

        break;
    }

    SpResult result(new Result());
    return result;
}


}
}
