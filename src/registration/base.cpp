#include <cpd/registration/base.hpp>

#include <cpd/exceptions.hpp>
#include <cpd/find_P.hpp>


namespace cpd
{
namespace registration
{


Base::Base(double tol, int max_it, double outliers, bool use_fgt)
    : m_tol(tol)
    , m_max_it(max_it)
    , m_outliers(outliers)
    , m_use_fgt(use_fgt)
{}


SpResult Base::operator()(const arma::mat& X, arma::mat& Y) const
{
    if (X.n_cols != Y.n_cols)
    {
        throw cpd::dimension_mismatch("X and Y do not have the same number of columns");
    }
    arma::mat Xn(X);
    Normalization normal = normalize(Xn, Y);
    SpResult result = execute(Xn, Y);
    denormalize(Y, normal);
    return result;
}


Normalization Base::normalize(arma::mat& X, arma::mat& Y) const
{
    Normalization normal;

    const arma::uword N = X.n_rows;
    const arma::uword M = Y.n_rows;

    normal.xd = arma::mean(X);
    normal.yd = arma::mean(Y);

    X = X - arma::repmat(normal.xd, N, 1);
    Y = Y - arma::repmat(normal.yd, M, 1);

    normal.xscale = std::sqrt(arma::sum(arma::sum(arma::pow(X, 2), 2)) / N);
    normal.yscale = std::sqrt(arma::sum(arma::sum(arma::pow(Y, 2), 2)) / M);

    X = X / normal.xscale;
    Y = Y / normal.yscale;

    return normal;
}


void Base::denormalize(arma::mat& Y, const Normalization& normal) const
{
    Y = Y * normal.xscale + arma::repmat(normal.xd, Y.n_rows, 1);
}


double Base::find_P(
        const arma::mat& X,
        const arma::mat& Y,
        double sigma2,
        arma::vec& P1,
        arma::vec& Pt1,
        arma::mat& PX
        ) const
{
    return cpd::find_P(X, Y, sigma2, get_outliers(), P1, Pt1, PX, use_fgt());
}


}
}
