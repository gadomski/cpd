#include <iostream>
#include <string>

#include <cpd/nonrigid.hpp>
#include <cpd/rigid.hpp>

void RigidCallback(const cpd::Result &r) {
  std::cout << r.points << std::endl << std::endl;
}

void NonrigidCallback(const cpd::NonrigidResult &r) {
  std::cout << r.points << std::endl << std::endl;
}

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
        cpd::Rigid rigid;
        auto *cb = RigidCallback;
        rigid.add_callback(cb);
        auto rigid_result = rigid.run(fixed, moving);
    } else if (method == "nonrigid") {
        cpd::Nonrigid nonrigid;
        auto *cb = NonrigidCallback;
        nonrigid.add_callback(cb);
        auto nonrigid_result = nonrigid.run(fixed, moving);
    } else {
        std::cout << "Invalid method: " << method << std::endl;
        return 1;
    }
    std::cout << "Registration completed OK" << std::endl;
    return 0;
}


