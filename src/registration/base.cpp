#include <cpd/registration/base.hpp>

#include <cpd/exceptions.hpp>


namespace cpd
{
namespace registration
{


Base::Base(float tol, int max_it, float outliers, bool use_fgt)
    : m_tol(tol)
    , m_max_it(max_it)
    , m_outliers(outliers)
    , m_use_fgt(use_fgt)
{}


SpResult Base::operator()(arma::mat& X, arma::mat& Y) const
{
    if (X.n_cols != Y.n_cols)
    {
        throw cpd::dimension_mismatch("X and Y do not have the same number of columns");
    }
    Normalization normal = normalize(X, Y);
    SpResult result = execute(X, Y);
    denormalize(result, normal);
    return result;
}


Normalization Base::normalize(arma::mat& X, arma::mat& Y) const
{
    Normalization normal = {};
    return normal;
}


void Base::denormalize(SpResult& result, const Normalization& normal) const
{}


double Base::find_P(
        const arma::mat& X,
        const arma::mat& Y,
        double sigma2,
        float outliers,
        arma::vec& P1,
        arma::vec& Pt1,
        arma::mat& PX
        ) const
{
    return 0;
}


}
}
