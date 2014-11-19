#pragma once

#include <cpd/registration/base.hpp>


namespace cpd
{
namespace registration
{


class Rigid : public Base
{
public:

    explicit Rigid(
            double tol = 1e-5,
            int max_it = 150,
            double outliers = 0.1,
            bool use_fgt = false,
            bool strict_rot = true,
            bool use_scaling = true
            );
    
    inline bool strict_rot() const { return m_strict_rot; }
    inline bool use_scaling() const { return m_use_scaling; }

private:
    virtual SpResult execute(const arma::mat& X, arma::mat& Y) const;

    bool m_strict_rot;
    bool m_use_scaling;

};


}
}
