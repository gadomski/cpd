/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
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

#pragma once

#include <armadillo>


namespace cpd {


void find_affinity_eigenvectors(const arma::mat& Y, const float beta,
                                const arma::uword numeig, const float epsilon,
                                arma::mat& Q, arma::mat& S);
void run_aupd(const arma::uword n_eigvals, char* which, const arma::mat& Y,
              arma::blas_int& n, double& tol, arma::podarray<double>& resid,
              arma::blas_int& ncv, arma::podarray<double>& v,
              arma::blas_int& ldv, arma::podarray<arma::blas_int>& iparam,
              arma::podarray<arma::blas_int>& ipntr,
              arma::podarray<double>& workd, arma::podarray<double>& workl,
              arma::blas_int& lworkl, arma::podarray<double>& rwork,
              arma::blas_int& info, const double beta, const float epsilon);
}
