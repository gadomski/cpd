#include <iostream>

#include <cpd/logging.hpp>
#include <cpd/rigid.hpp>
#include <cpd/utils.hpp>
#include <cpd/vendor/spdlog/spdlog.h>

int main(int argc, char** argv) {
    auto logger = spdlog::stdout_logger_mt(cpd::LOGGER_NAME);
    if (argc != 3) {
        logger->critical("Invalid number of arguments");
        logger->info("USAGE: rigid <fixed> <moving>");
        return 1;
    }
    cpd::Matrix fixed = cpd::matrix_from_path(argv[1]);
    cpd::Matrix moving = cpd::matrix_from_path(argv[2]);
    cpd::Rigid::Result result = cpd::rigid(fixed, moving);
    std::cout << result << std::endl;
    return 0;
}
