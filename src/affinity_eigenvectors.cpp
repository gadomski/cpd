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

#include "affinity_eigenvectors.hpp"

#include "debug.hpp"
#include "exceptions.hpp"

#include <fgt/fgt.hpp>


// This whole setup is a relatively magical rewiring of armadillo's
// sp_auxlib::eigs_sym
// and sp_auxlib::run_aupd. I rewired it all to insert our call to fgt in
// the aupd
// run.
//
// I didn't put too much effort into parametrizing all of this, since it's a
// very
// specific use-case for our setup.
//
// -pjg
namespace cpd {


void run_aupd(const arma::uword n_eigvals, char* which, const arma::mat& Y,
              arma::blas_int& n, double& tol, arma::podarray<double>& resid,
              arma::blas_int& ncv, arma::podarray<double>& v,
              arma::blas_int& ldv, arma::podarray<arma::blas_int>& iparam,
              arma::podarray<arma::blas_int>& ipntr,
              arma::podarray<double>& workd, arma::podarray<double>& workl,
              arma::blas_int& lworkl, arma::podarray<double>& rwork,
              arma::blas_int& info, const double beta, const float epsilon) {
    double h = std::sqrt(2) * beta;
    fgt::GaussTransformUnqPtr transform =
        fgt::choose_gauss_transform(Y, h, epsilon);

    arma::blas_int ido = 0;
    char bmat = 'I';
    n = arma::blas_int(Y.n_rows);
    arma::blas_int nev = arma::blas_int(n_eigvals);

    resid.set_size(Y.n_rows);

    ncv = 2 + nev;
    if (ncv < 2 * nev) {
        ncv = 2 * nev;
    }
    if (ncv > n) {
        ncv = n;
    }
    v.set_size(arma::uword(n * ncv));
    rwork.set_size(arma::uword(ncv));
    ldv = n;

    iparam.zeros(11);
    iparam(0) = 1;
    iparam(2) = 1000;
    iparam(6) = 1;

    ipntr.set_size(14);

    workd.set_size(3 * arma::uword(n));

    lworkl = 3 * (ncv * ncv) + 6 * ncv;

    workl.set_size(arma::uword(lworkl));

    info = 0;

    while (ido != 99) {
        arma::arpack::saupd(&ido, &bmat, &n, which, &nev, &tol, resid.memptr(),
                            &ncv, v.memptr(), &ldv, iparam.memptr(),
                            ipntr.memptr(), workd.memptr(), workl.memptr(),
                            &lworkl, &info);

        switch (ido) {
        case -1:
        case 1: {
            arma::Col<double> out(workd.memptr() + ipntr(1) - 1, arma::uword(n),
                                  false);
            arma::Col<double> in(workd.memptr() + ipntr(0) - 1, arma::uword(n),
                                 false);

            out = transform->compute(Y, in);
            break;
        }
        case 99:
            break;
        default: { return; }
        }
    }

    if ((info != 0) && (info != 1)) {
        std::stringstream tmp;
        tmp << "ARPACK error " << info << " when running saupd()";
        throw arpack_error(tmp.str());
    }
}


void find_affinity_eigenvectors(const arma::mat& Y, const float beta,
                                const arma::uword numeig, const float epsilon,
                                arma::mat& Q, arma::mat& S) {
    char which[3] = "LM";
    arma::blas_int n, ncv, ldv, lworkl, info;
    double tol = 0.0;
    arma::podarray<double> resid, v, workd, workl;
    arma::podarray<arma::blas_int> iparam, ipntr;
    arma::podarray<double> rwork;

    DEBUG("running aupd");
    run_aupd(numeig, which, Y, n, tol, resid, ncv, v, ldv, iparam, ipntr, workd,
             workl, lworkl, rwork, info, beta, epsilon);
    DEBUG("done with aupd");

    arma::blas_int rvec = 1;
    arma::blas_int nev = arma::blas_int(numeig);
    char howmny = 'A';
    char bmat = 'I';

    arma::podarray<arma::blas_int> select((arma::uword(ncv)));
    arma::blas_int ldz = n;

    arma::vec s(numeig);
    Q.set_size(arma::uword(n), numeig);

    DEBUG("running seupd");
    arma::arpack::seupd(&rvec, &howmny, select.memptr(), s.memptr(), Q.memptr(),
                        &ldz, static_cast<double*>(nullptr), &bmat, &n, which, &nev, &tol,
                        resid.memptr(), &ncv, v.memptr(), &ldv, iparam.memptr(),
                        ipntr.memptr(), workd.memptr(), workl.memptr(), &lworkl,
                        &info);
    DEBUG("done with seupd");

    if (info != 0) {
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
