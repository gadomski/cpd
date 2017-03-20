/// Create two random datasets and run cpd on them.
///
/// This is mostly to test for behavior when running overly-large data through
/// nonrigid (#104).

#include <iostream>
#include <string>

#include <cpd/nonrigid.hpp>
#include <cpd/rigid.hpp>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Invalid usage: cpd-random <method> <rows> <cols>"
                  << std::endl;
        return 1;
    }
    std::string method = argv[1];
    size_t rows = std::stoi(argv[2]);
    size_t cols = std::stoi(argv[3]);
    cpd::Matrix fixed = cpd::Matrix::Random(rows, cols);
    cpd::Matrix moving = cpd::Matrix::Random(rows, cols);

    if (method == "rigid") {
        cpd::rigid(fixed, moving);
    } else if (method == "nonrigid") {
        cpd::nonrigid(fixed, moving);
    } else {
        std::cout << "Invalid method: " << method << std::endl;
        return 1;
    }
    std::cout << "Registration completed OK" << std::endl;
    return 0;
}
