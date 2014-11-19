#pragma once

#include <armadillo>


namespace cpd
{


void find_affinity_eigenvectors(const arma::mat& Y, double beta, int numeig, arma::mat& Q, arma::mat& S);


}
