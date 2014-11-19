#pragma once

#include <armadillo>

#include <cpd/registration/normalization.hpp>
#include <cpd/registration/result.hpp>


namespace cpd
{
namespace registration
{


class Base
{
public:

    explicit Base(
            double tol = 1e-5,
            int max_it = 150,
            double outliers = 0.1,
            bool use_fgt = false
            );

    SpResult operator()(const arma::mat& X, const arma::mat& Y) const;
    Normalization normalize(arma::mat& X, arma::mat& Y) const;
    void denormalize(arma::mat& Y, const Normalization& normal) const;

    double find_P(
            const arma::mat& X,
            const arma::mat& Y,
            double sigma2,
            arma::vec& P1,
            arma::vec& Pt1,
            arma::mat& PX
            ) const;

    inline double get_tol() const { return m_tol; }
    inline int get_max_it() const { return m_max_it; }
    inline double get_outliers() const { return m_outliers; }
    inline bool use_fgt() const { return m_use_fgt; }

    inline void set_tol(double tol) { m_tol = tol; }
    inline void set_max_it(int max_it) { m_max_it = max_it; }
    inline void set_outliers(double outliers) { m_outliers = outliers; }
    inline void use_fgt(bool use_fgt) { m_use_fgt = use_fgt; }

    virtual ~Base() {};

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const = 0;

    double m_tol;
    int m_max_it;
    double m_outliers;
    bool m_use_fgt;

};


}
}
