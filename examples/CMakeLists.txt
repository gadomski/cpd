project(cpd-examples CXX)
cmake_minimum_required(VERSION 2.8.12)

find_package(Cpd REQUIRED)
find_package(PDAL)

function(cpd_example name)
    set(target ${name}-example)
    add_executable(${target} ${name}.cpp)
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${name})
    target_link_libraries(${target} PRIVATE Cpd::Library-C++ ${ARGN})
endfunction()

cpd_example(rigid)
if(PDAL_FOUND)
    cpd_example(artificial-displacement pdalcpp)
endif()
