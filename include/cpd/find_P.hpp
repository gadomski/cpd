#pragma once

#include <armadillo>


namespace cpd
{


double find_P(
        const arma::mat& X,
        const arma::mat& Y,
        double sigma2,
        float outliers,
        arma::vec& P1,
        arma::vec& Pt1,
        arma::mat& PX,
        bool use_fgt
        );

}
