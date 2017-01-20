project(cpd-examples CXX)
cmake_minimum_required(VERSION 2.8.12)

find_package(Cpd COMPONENTS jsoncpp REQUIRED)
add_executable(cpd-rigid rigid.cpp)
target_link_libraries(cpd-rigid PRIVATE Cpd::Library-C++ Cpd::Jsoncpp)

find_package(Cpd REQUIRED)
add_executable(cpd-version version.cpp)
target_link_libraries(cpd-version PRIVATE Cpd::Library-C++)
