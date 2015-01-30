# Setup
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpd CXX C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MACOSX_RPATH ON)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified, setting to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)


# Version
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(CPD_VERSION_DESCRIBE)
string(SUBSTRING ${CPD_VERSION_DESCRIBE} 1 -1 CPD_VERSION)
set(CPD_SOVERSION 0)
message(STATUS "cpd version ${CPD_VERSION}")


# Options
option(BUILD_CLI "Build the command-line interface" OFF)
option(BUILD_COVERAGE "Build with code coverage support" OFF)
option(BUILD_DEBUG_OUTPUT "Build with debug output" OFF)
option(BUILD_SHARED_LIBS "Create shared libraries" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_64BIT "Build with 64 bit matrix support" ON)

if (WIN32)
    set(USE_ARMA_WRAPPER OFF)
else(WIN32)
    option(USE_ARMA_WRAPPER "Use the armadillo wrapper library" ON)
endif(WIN32)


# Checks
if (BUILD_COVERAGE)
    if (NOT BUILD_TESTS)
        message(FATAL_ERROR "Cannot build coverage without tests, set BUILD_TESTS to ON")
    endif(NOT BUILD_TESTS)
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
    endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(BUILD_COVERAGE)


# Configuration
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
if (BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "--coverage ${CMAKE_CXX_FLAGS}")
    endif(CMAKE_COMPILER_IS_GNUCXX)
endif(BUILD_COVERAGE)


# Definitions
if (BUILD_DEBUG_OUTPUT)
    add_definitions(-DCPD_DEBUG_OUTPUT)
endif(BUILD_DEBUG_OUTPUT)

if (NOT USE_ARMA_WRAPPER)
    add_definitions(-DARMA_DONT_USE_WRAPPER)
endif()


# Targets and directories
set(CPD_CLI_TARGET cpd-cli)
set(CPD_LIB_TARGET cpd-lib)
set(CPD_TEST_TARGET cpd-test)
set(CPD_COVERAGE_TARGET coverage)
set(CPD_PERFORMANCE_TEST_TARGET cpd-performance)
set(CPD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(CPD_LIB_NAME cpd)

set(CPD_EXPORT CPDTargets)


# Output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# Dependencies
find_package(Armadillo 4.500.1 REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(Figtree REQUIRED)
include_directories(${FIGTREE_INCLUDE_DIRS})

if (NOT USE_ARMA_WRAPPER)
    find_package(ARPACK REQUIRED)
    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_library(ACCELERATE_LIBRARY Accelerate)
    else(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_package(BLAS REQUIRED)
        find_package(LAPACK REQUIRED)
    endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
endif(NOT USE_ARMA_WRAPPER)


# Includes
add_subdirectory(include)
add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(vendor/gtest-1.7.0)
    add_subdirectory(test)
endif (BUILD_TESTS)

if(BUILD_CLI)
    add_subdirectory(cli)
endif(BUILD_CLI)


# CPDConfig.cmake
include(CMakePackageConfigHelpers)

set(LIB_INSTALL_DIR lib)
set(INCLUDE_INSTALL_DIR include)

configure_package_config_file(
    CPDConfig.cmake.in
    ${PROJECT_BINARY_DIR}/CPDConfig.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cpd/cmake
    PATH_VARS INCLUDE_INSTALL_DIR
    )
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/CPDConfigVersion.cmake
    VERSION ${CPD_VERSION}
    COMPATIBILITY SameMajorVersion
    )
export(TARGETS ${CPD_LIB_TARGET} FILE ${PROJECT_BINARY_DIR}/CPDTargets.cmake)

install(
    FILES
        ${PROJECT_BINARY_DIR}/CPDConfig.cmake
        ${PROJECT_BINARY_DIR}/CPDConfigVersion.cmake
    DESTINATION
        ${LIB_INSTALL_DIR}/cpd/cmake
    )
install(
    EXPORT ${CPD_EXPORT}
    DESTINATION ${LIB_INSTALL_DIR}/cpd/cmake
    )
