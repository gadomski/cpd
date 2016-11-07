/// Reads a point cloud, applies an artifical translation, then recovers it.
///
/// This example uses [PDAL](http://www.pdal.io/) to read a point cloud file.
/// The points are then translated, and the translation is recovered with rigid
/// CPD.
/// This examples demonstrates configuring the runner, comparer, and
/// transformation.

#include <cpd/comparer.hpp>
#include <cpd/logging.hpp>
#include <cpd/matrix.hpp>
#include <cpd/rigid.hpp>
#include <cpd/runner.hpp>
#include <cpd/vendor/spdlog/spdlog.h>
#include <iostream>
#include <pdal/EigenUtils.hpp>
#include <pdal/Options.hpp>
#include <pdal/Stage.hpp>
#include <pdal/StageFactory.hpp>

cpd::Matrix read_cropped_matrix(const std::string& infile) {
    pdal::StageFactory factory;

    pdal::Stage* reader(factory.createStage(factory.inferReaderDriver(infile)));
    pdal::Options reader_options;
    reader_options.add("filename", infile);
    reader->setOptions(reader_options);

    pdal::PointTable table;
    reader->prepare(table);
    pdal::PointViewSet viewSet = reader->execute(table);
    return pdal::eigen::pointViewToEigen(**viewSet.begin());
}

cpd::Rigid::Result recover_translation(const cpd::Matrix& fixed,
                                       const Eigen::Vector3d& translation) {
    assert(fixed.rows() != 0);
    cpd::Matrix moving =
        fixed + translation.transpose().replicate(fixed.rows(), 1);
    cpd::FgtComparer comparer;
    comparer.method(cpd::FgtMethod::DirectTree);
    cpd::Rigid rigid;
    rigid.scale(false);
    cpd::Runner<cpd::Rigid, cpd::FgtComparer> runner(rigid, comparer);
    runner.sigma2(0.2);
    return runner.run(moving, fixed);
}

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "ERROR: Invalid number of arguments" << std::endl;
        std::cout
            << "USAGE: artificial-displacement <infile> <x> <y> <z> <outfile>"
            << std::endl;
        return 1;
    }
    auto logger = spdlog::stdout_logger_mt(cpd::LOGGER_NAME);
    std::string infile = argv[1];
    double x_translation = std::stod(argv[2]);
    double y_translation = std::stod(argv[3]);
    double z_translation = std::stod(argv[4]);
    std::string outfile = argv[5];
    cpd::Matrix matrix = read_cropped_matrix(infile);
    Eigen::Vector3d translation(x_translation, y_translation, z_translation);
    cpd::Rigid::Result result = recover_translation(matrix, translation);
    std::ofstream ofstream(outfile);
    ofstream << result << std::endl;
    ofstream.close();
    return 0;
}
