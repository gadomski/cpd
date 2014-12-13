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

#include <gflags/gflags.h>

#include <cpd/nonrigid_lowrank.hpp>


using namespace cpd;


DEFINE_int32(precision, 3, "Output precision");
DEFINE_string(method, "nonrigid_lowrank", "Registration method");
DEFINE_double(tol, DEFAULT_TOLERANCE, "Tolerance ctriterium");
DEFINE_int32(max_it, DEFAULT_MAX_ITERATIONS, "Maximum number of iterations");
DEFINE_double(outliers, DEFAULT_OUTLIERS, "The weight of noise and outliers");
DEFINE_bool(fgt, DEFAULT_FGT, "Use a Fast Gauss Transform");
DEFINE_double(epsilon, DEFAULT_EPSILON, "The tolerance of the Fast Gauss Transform");
DEFINE_double(beta, DEFAULT_BETA, "Std of Gaussian filter");
DEFINE_double(lambda, DEFAULT_LAMBDA, "Regularization weight");
DEFINE_double(numeig, DEFAULT_NUMEIG, "Number of the largest eigenvectors to use, try NumPoints^(1/2). If zero, will be auto-calculated.");
    

int main(int argc, char** argv)
{
    gflags::SetUsageMessage("usage: cpd file1.txt file2.txt");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (argc == 1)
    {
        gflags::ShowUsageWithFlags("cpd");
        return 0;
    }
    if (argc != 3)
    {
        std::cerr << "ERROR: cpd requires two input files" << std::endl;
        gflags::ShowUsageWithFlags("cpd");
        return 1;
    }
    std::string fileX = argv[1];
    std::string fileY = argv[2];    
    arma::mat X, Y;
    if (!X.load(fileX))
    {
        std::cerr << "ERROR: unable to open file '" << fileX << "'" << std::endl;
        return 1;
    }
    if (!Y.load(fileY))
    {
        std::cerr << "ERROR: unable to open file '" << fileY << "'" << std::endl;
        return 1;
    }

    if (FLAGS_method != "nonrigid_lowrank")
    {
        std::cerr << "ERROR: currently, only nonrigid_lowrank is supported" << std::endl;
        return 1;
    }
    cpd::NonrigidLowrank reg(
        FLAGS_tol,
        FLAGS_max_it,
        FLAGS_outliers,
        FLAGS_fgt,
        FLAGS_epsilon,
        FLAGS_beta,
        FLAGS_lambda,
        FLAGS_numeig
        );
    cpd::Registration::ResultPtr result = reg.run(X, Y);

    std::cout.precision(FLAGS_precision);
    std::cout << std::fixed;
    arma::join_horiz(result->Y, Y - result->Y).raw_print(std::cout);

    return 0;
}
