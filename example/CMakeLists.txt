cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpd-example-project CXX)

find_package(CPD REQUIRED)

# find_package(CPD) sets CPD_INCLUDE_DIRS to the appropriate
# value
include_directories(${CPD_INCLUDE_DIRS})

add_executable(cpd-example-project main.cpp)

# If CPD was built with ARMA_64BIT_WORD defined, your application
# must also define the macro. Otherwise, you will probably get
# an undefined symbol error when building.
#
# See https://github.com/gadomski/cpd/issues/20 for a discussion
# of this issue.
add_definitions(-DARMA_64BIT_WORD)

# find_package(CPD) imports all necessary targets and
# sets some useful properties of those targets, so all that
# needs to be done from here is to link against the 
# `cpd-lib` target.
target_link_libraries(cpd-example-project cpd-lib)
