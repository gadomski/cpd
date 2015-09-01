cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpd-example-project CXX)

find_package(CPD REQUIRED)

add_executable(cpd-example-project main.cpp)

# find_package(CPD) imports all necessary targets and
# sets some useful properties of those targets, so all that
# needs to be done from here is to link against the 
# `cpd-lib` target.
target_link_libraries(cpd-example-project Cpd::Library)
