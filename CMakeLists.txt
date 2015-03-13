# Setup
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpd CXX C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified, setting to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()


# RPath
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_SKIP_BUILD_RPATH  OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()


# Version
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(CPD_VERSION_DESCRIBE)
string(SUBSTRING ${CPD_VERSION_DESCRIBE} 1 -1 CPD_VERSION)
set(CPD_SOVERSION 0)
message(STATUS "cpd version ${CPD_VERSION}")


# Options
option(ARMA_64BIT_WORD "Use 64 bit words for armadillo" ON)
option(ARMA_NO_DEBUG "Disable range checks in armadillo" OFF)
option(BUILD_CLI "Build the command-line interface" OFF)
option(BUILD_COVERAGE "Build with code coverage support" OFF)
option(BUILD_DEBUG_OUTPUT "Build with debug output" OFF)
option(BUILD_SHARED_LIBS "Create shared libraries" ON)
option(BUILD_TESTS "Build tests" ON)


# Checks
if(BUILD_COVERAGE)
    if(NOT BUILD_TESTS)
        message(FATAL_ERROR "Cannot build coverage without tests, set BUILD_TESTS to ON")
    endif()
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
    endif()
endif()


# Configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "--coverage ${CMAKE_CXX_FLAGS}")
    endif()
endif()


# Definitions
if(BUILD_DEBUG_OUTPUT)
    add_definitions(-DCPD_DEBUG_OUTPUT)
endif()


# Output paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


# Dependencies
find_package(Armadillo 4.600.1 REQUIRED)
find_package(Fgt 0.1.0 REQUIRED)


# rpath
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()


# Includes and targets
include(cmake/configure_target.cmake)
set(CPD_EXPORT CPDTargets)

add_subdirectory(include)
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(vendor/gtest-1.7.0)
    add_subdirectory(test)
endif()

if(BUILD_CLI)
    add_subdirectory(cli)
endif()


# CPDConfig.cmake
include(CMakePackageConfigHelpers)

set(LIB_INSTALL_DIR lib)
set(INCLUDE_INSTALL_DIR include)

configure_package_config_file(
    cmake/CPDConfig.cmake.in
    ${PROJECT_BINARY_DIR}/CPDConfig.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cpd/cmake
    PATH_VARS INCLUDE_INSTALL_DIR
    )
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/CPDConfigVersion.cmake
    VERSION ${CPD_VERSION}
    COMPATIBILITY SameMajorVersion
    )
export(TARGETS cpd-lib FILE ${PROJECT_BINARY_DIR}/CPDTargets.cmake)

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
