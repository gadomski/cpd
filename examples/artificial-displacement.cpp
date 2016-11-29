/// Reads a point cloud, applies an artificial translation (with some noise),
/// then recovers that translation.
///
/// This example uses [PDAL](http://www.pdal.io/) to read a point cloud file.
/// The points are then translated, and the translation is recovered with rigid
/// CPD. This examples demonstrates configuring the runner, comparer, and
/// transformation.

#include "docopt.h"
#include <Eigen/Dense>
#include <cpd/comparer/base.hpp>
#include <cpd/matrix.hpp>
#include <cpd/rigid.hpp>
#include <cpd/runner.hpp>
#include <pdal/EigenUtils.hpp>
#include <pdal/StageFactory.hpp>
#include <random>

static const char USAGE[] =
    R"(Artificial displacement and noise testing of a rigid transformation.

Usage:
    artificial-displacement <infile> <x> <y> <z> <stddev> [--bounds=<wkt>] [--comparer=<name>] [--sigma2=<n>]

Options:
    -h --help               Show this screen.
    --bounds=<wkt>          Crop the data to these bounds.
    --comparer=<name>       Comparer to use (direct or fgt) [default: fgt].
    --sigma2=<n>            Initial sigma2 [default: 0.0].
)";

cpd::Matrix read_matrix(const std::string& infile, const std::string& bounds);
cpd::Matrix create_noise_matrix(cpd::Matrix::Index rows,
                                cpd::Matrix::Index cols, double stddev);

int main(int argc, char** argv) {
    auto log = spdlog::stderr_logger_mt(cpd::LOGGER_NAME);
    std::map<std::string, docopt::value> args =
        docopt::docopt(USAGE, { argv + 1, argv + argc }, true,
                       "CPD artificial displacement", true);
    cpd::Matrix original = read_matrix(args.at("<infile>").asString(),
                                       args.at("--bounds").asString());
    Eigen::Vector3d translation(std::stod(args.at("<x>").asString()),
                                std::stod(args.at("<y>").asString()),
                                std::stod(args.at("<z>").asString()));
    cpd::Matrix noise =
        create_noise_matrix(original.rows(), original.cols(),
                            std::stod(args.at("<stddev>").asString()));
    cpd::Matrix modified =
        original + translation.transpose().replicate(original.rows(), 1) +
        noise;
    cpd::Rigid rigid;
    rigid.allow_reflections(false).scale(false);
    cpd::Runner<cpd::Rigid> runner(rigid);
    std::unique_ptr<cpd::Comparer> comparer =
        cpd::Comparer::from_name(args.at("--comparer").asString());
    runner.comparer(std::move(comparer))
        .normalize(true)
        .sigma2(std::stod(args.at("--sigma2").asString()));
    cpd::Rigid::Result result = runner.run(modified, original);
    cpd::Vector calculated_translation =
        (result.points - original).colwise().mean();
    Eigen::IOFormat format(3, 0, ", ", ", ", "", "", "", "");
    std::cout << std::fixed << calculated_translation.format(format) << ", "
              << (translation - calculated_translation).format(format)
              << std::endl;
    return 0;
}

cpd::Matrix read_matrix(const std::string& infile, const std::string& bounds) {
    pdal::StageFactory factory(false);
    std::string driver = factory.inferReaderDriver(infile);
    pdal::Stage* reader = factory.createStage(driver);
    pdal::Options reader_options;
    reader_options.add("filename", infile);
    reader->setOptions(reader_options);
    pdal::Stage* stage = reader;
    if (!bounds.empty()) {
        stage = factory.createStage("filters.crop");
        stage->setInput(*reader);
        pdal::Options crop_options;
        crop_options.add("bounds", bounds);
        stage->setOptions(crop_options);
    }
    pdal::PointTable table;
    stage->prepare(table);
    pdal::PointViewSet pointViewSet = stage->execute(table);
    return pdal::eigen::pointViewToEigen(**pointViewSet.begin());
}

cpd::Matrix create_noise_matrix(cpd::Matrix::Index rows,
                                cpd::Matrix::Index cols, double stddev) {
    std::random_device device;
    std::default_random_engine engine(device());
    std::normal_distribution<> distribution(0.0, stddev);
    cpd::Matrix noise(rows, cols);
    for (cpd::Matrix::Index i = 0; i < noise.rows(); ++i) {
        for (cpd::Matrix::Index j = 0; j < noise.cols(); ++j) {
            noise(i, j) = distribution(engine);
        }
    }
    return noise;
}
