#include <gflags/gflags.h>

#include <cpd/registration/nonrigid_lowrank.hpp>


DEFINE_int32(precision, 3, "Output precision");
DEFINE_string(method, "nonrigid_lowrank", "Registration method");
DEFINE_double(tol, 1e-5, "Tolerance ctriterium");
DEFINE_int32(max_it, 150, "Maximum number of iterations");
DEFINE_double(outliers, 0.1, "The weight of noise and outliers");
DEFINE_bool(fgt, true, "Use a Fast Gauss Transform");
DEFINE_double(beta, 2, "Std of Gaussian filter");
DEFINE_double(lambda, 3, "Regularization weight");
DEFINE_double(numeig, 100, "Number of the largest eigenvectors to use, try NumPoints^(1/2)");
    

int main(int argc, char** argv)
{
    gflags::SetUsageMessage("usage: cpd file1.txt file2.txt");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
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
    cpd::registration::NonrigidLowrank reg(
        FLAGS_tol,
        FLAGS_max_it,
        FLAGS_outliers,
        FLAGS_fgt,
        FLAGS_beta,
        FLAGS_lambda,
        FLAGS_numeig
        );
    cpd::registration::SpResult result = reg(X, Y);

    std::cout.precision(FLAGS_precision);
    std::cout << std::fixed;
    arma::join_horiz(result->Y, result->Y - Y).raw_print(std::cout);

    return 0;
}
