/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
* 
* Derived from the Coherent Point Drift Matlab package
* Copyright (C) 2008-2009 Andriy Myronenko <myron@csee.ogi.edu>
* https://sites.google.com/site/myronenko/research/cpd
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#include <cpd/affinity_eigenvectors.hpp>

#include <cpd/affinity_matrix.hpp>


namespace cpd
{


void find_affinity_eigenvectors(const arma::mat& Y, double beta, int numeig, arma::mat& Q, arma::mat& S)
{
    const arma::uword M = Y.n_rows;
    const double h = std::sqrt(2) * beta;
    arma::mat G(M, M);
    construct_affinity_matrix(Y, Y, beta, G);

    arma::mat Qf;
    arma::vec s;
    arma::eig_sym(s, Qf, G);

    S.zeros(numeig, numeig);
    S.diag() = arma::flipud(s.subvec(M - numeig, M - 1));

    Q.zeros(numeig, numeig);
    Q = arma::fliplr(Qf.submat(0, M - numeig, M - 1, M - 1));
}


}
