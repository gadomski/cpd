#include <iostream>

#include <cpd/nonrigid_lowrank.hpp>


void print_usage(char * program)
{
    std::cerr << "Usage: " << program << " filename_X filenameY"
        << std::endl;
}


// This example application reads two files and outputs the CPD
// registration (wtih deltas) to stdout.
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Error: " << argv[0]
            << " must be run with two arguments" << std::endl;
        print_usage(argv[0]);
        return 1;
    }

    // Registrations take two arma::mat objects as their arguments.
    // This demonstrates one way to create an arma::mat —
    // see http://arma.sourceforge.net/docs.html
    // for more examples.
    arma::mat X;
    X.load(argv[1]);
    arma::mat Y;
    Y.load(argv[2]);

    // To use other types of registrations (e.g. rigid) include the
    // appropriate header and construct a registration of the
    // appropriate type.
    cpd::NonrigidLowrank reg;
    cpd::Registration::ResultPtr result = reg.run(X, Y);
    
    // For an extra twist, we include the deltas for each point.
    arma::mat output = result->Y;
    output.insert_cols(output.n_cols, Y - output);
    output.save(std::cout, arma::csv_ascii);
}
