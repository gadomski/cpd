#pragma once

#include <cpd/registration/nonrigid.hpp>


namespace cpd
{
namespace registration
{


class NonrigidLowrank : public Nonrigid
{
public:

    explicit NonrigidLowrank(
            double tol = 1e-5,
            int max_it = 150,
            double outliers = 0.1,
            bool use_fgt = false,
            double beta = 2,
            double lambda =  3,
            int numeig = 10
            );

    inline int get_numeig() const { return m_numeig; }

    inline void set_numeig(int numeig) { m_numeig = numeig; }

private:

    virtual SpResult execute(const arma::mat& X, const arma::mat& Y) const;

    int m_numeig;

};


}
}
