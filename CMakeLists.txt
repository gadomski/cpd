# Setup
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(cpd CXX)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_BUILD_TYPE Release)


# Options
option(BUILD_CLI "Build the command-line interface" OFF)
option(BUILD_SHARED_LIBS "Create shared libraries" ON)
option(BUILD_TESTS "Build tests (requires gtest)" ON)


# Targets and directories
set(CPD_CLI_TARGET cpd-cli)
set(CPD_LIB_TARGET cpd-lib)
set(CPD_TEST_TARGET cpd-test)
set(CPD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")


# Output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# Dependencies
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(Figtree REQUIRED)
include_directories(${FIGTREE_INCLUDE_DIRS})


# Includes
add_subdirectory(src)

if (BUILD_TESTS)
    add_subdirectory(vendor/gtest-1.7.0)
    add_subdirectory(test)
endif (BUILD_TESTS)

if(BUILD_CLI)
    add_subdirectory(cli)
endif(BUILD_CLI)
