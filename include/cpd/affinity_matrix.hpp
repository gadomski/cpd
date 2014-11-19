#pragma once

#include <armadillo>


namespace cpd
{


void construct_affinity_matrix(const arma::mat& X, const arma::mat& Y, double beta, arma::mat& G);


}
