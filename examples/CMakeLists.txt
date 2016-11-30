project(cpd-examples CXX)
cmake_minimum_required(VERSION 2.8.12)
include(CMakeParseArguments)
set(DOCOPT_DIR "../vendor/docopt.cpp-af03fa0")

find_package(Cpd REQUIRED)
find_package(PDAL QUIET)

function(cpd_example name)
    set(target ${name}-example)
    set(multi_value_args ADDITIONAL_SOURCES LINK_LIBRARIES INCLUDE_DIRECTORIES)
    cmake_parse_arguments(cpd_example "" "" "${multi_value_args}" ${ARGN})
    add_executable(${target} ${name}.cpp ${cpd_example_ADDITIONAL_SOURCES})
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${name})
    target_link_libraries(${target} PRIVATE Cpd::Library-C++ ${cpd_example_LINK_LIBRARIES})
    target_include_directories(${target} PRIVATE ${cpd_example_INCLUDE_DIRECTORIES})
endfunction()

option(WITH_RIGID "Build the rigid registration example" ON)
if(${WITH_RIGID})
    cpd_example(rigid)
endif()

option(WITH_ARTIFICIAL_DISPLACEMENT "Build the artificial displacement example (requires PDAL)" ${PDAL_FOUND})
if(${WITH_ARTIFICIAL_DISPLACEMENT})
    find_package(PDAL REQUIRED)
    cpd_example(artificial-displacement
        ADDITIONAL_SOURCES "${DOCOPT_DIR}/docopt.cpp"
        INCLUDE_DIRECTORIES "${DOCOPT_DIR}"
        LINK_LIBRARIES ${PDAL_LIBRARIES})
endif()
