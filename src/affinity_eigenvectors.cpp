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

#include <cpd/exceptions.hpp>
#include <cpd/figtree.hpp>


// This whole setup is a relatively magical rewiring of armadillo's sp_auxlib::eigs_sym
// and sp_auxlib::run_aupd. I rewired it all to insert our call to figtree in the aupd
// run.
//
// I didn't put too much effort into parametrizing all of this, since it's a very
// specific use-case for our setup.
//
// -pjg
namespace cpd
{


void run_aupd(
        const arma::uword n_eigvals,
        char* which,
        arma::mat& Yt,
        arma::blas_int& n,
        double& tol,
        arma::podarray<double>& resid,
        arma::blas_int& ncv,
        arma::podarray<double>& v,
        arma::blas_int& ldv,
        arma::podarray<arma::blas_int>& iparam,
        arma::podarray<arma::blas_int>& ipntr,
        arma::podarray<double>& workd,
        arma::podarray<double>& workl,
        arma::blas_int& lworkl,
        arma::podarray<double>& rwork,
        arma::blas_int& info,
        const double beta,
        const float epsilon
        )
{    
    const arma::uword D = Yt.n_rows;
    const arma::uword M = Yt.n_cols;
    double h = std::sqrt(2) * beta;

    arma::blas_int ido = 0;
    char bmat = 'I';
    n = Yt.n_cols;
    arma::blas_int nev = n_eigvals;

    resid.set_size(n);

    ncv = 2 + nev;
    if (ncv < 2 * nev) { ncv = 2 * nev; }
    if (ncv > n)       { ncv = n; }
    v.set_size(n * ncv);
    rwork.set_size(ncv);
    ldv = n;

    iparam.zeros(11);
    iparam(0) = 1;
    iparam(2) = 1000;
    iparam(6) = 1;

    ipntr.set_size(14);

    workd.set_size(3 * n);

    lworkl = 3 * (ncv * ncv) + 6 * ncv;

    workl.set_size(lworkl);

    info = 0;

    while (ido != 99)
    {
        arma::arpack::saupd(&ido, &bmat, &n, which, &nev, &tol, resid.memptr(),
                            &ncv, v.memptr(), &ldv, iparam.memptr(), ipntr.memptr(),
                            workd.memptr(), workl.memptr(), &lworkl, &info);

        switch (ido)
        {
            case -1:
            case 1:
                {
                arma::Col<double> out(workd.memptr() + ipntr(1) - 1, n, false); 
                arma::Col<double> in(workd.memptr() + ipntr(0) - 1, n, false); 

                out.zeros();
                figtree_wrap(Yt, Yt, in, h, epsilon, out, FIGTREE_EVAL_AUTO);
                break;
                }
            case 99:
                break;
            default:
                {
                return;
                }
        }
    }

    if ((info != 0) && (info != 1))
    {
        std::stringstream tmp;
        tmp << "ARPACK error " << info << " when running saupd()";
        throw arpack_error(tmp.str());
    }

}


void find_affinity_eigenvectors(const arma::mat& Y, const float beta, const arma::uword numeig,
                                const float epsilon, arma::mat& Q, arma::mat& S)
{
    arma::mat Yt = Y.t();
    
    char which[3] = "LM";
    arma::blas_int n, ncv, ldv, lworkl, info;
    double tol = 0.0;
    arma::podarray<double> resid, v, workd, workl;
    arma::podarray<arma::blas_int> iparam, ipntr;
    arma::podarray<double> rwork;

    run_aupd(numeig, which, Yt, n, tol, resid, ncv, v, ldv, iparam, ipntr,
             workd, workl, lworkl, rwork, info, beta, epsilon);

    arma::blas_int rvec = 1;
    arma::blas_int nev = numeig;
    char howmny = 'A';
    char bmat = 'I';

    arma::podarray<arma::blas_int> select(ncv);
    arma::blas_int ldz = n;

    arma::vec s(numeig);
    Q.set_size(n, numeig);

    arma::arpack::seupd(&rvec, &howmny, select.memptr(), s.memptr(), Q.memptr(),
                        &ldz, (double*) NULL, &bmat, &n, which, &nev, &tol, resid.memptr(),
                        &ncv, v.memptr(), &ldv, iparam.memptr(), ipntr.memptr(),
                        workd.memptr(), workl.memptr(), &lworkl, &info);

    if (info != 0)
    {
        std::stringstream tmp;
        tmp << "ARPACK error " << info << " when running neupd()";
        throw arpack_error(tmp.str());
    }

    // The output matrices are setup like this to mirror the output of
    // Matlab's `eigs`
    S.zeros(numeig, numeig);
    S.diag() = arma::flipud(s);

    Q = arma::fliplr(Q);
}


}
