# Top-level cmakelists for cpd

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpd CXX C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set(ARMA_MINIMUM_VERSION 4.650.1)


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

message(STATUS "cpd options:
       ARMA_64BIT_WORD: ${ARMA_64BIT_WORD}
       ARMA_NO_DEBUG: ${ARMA_NO_DEBUG}
       BUILD_DEBUG_OUTPUT: ${BUILD_DEBUG_OUTPUT}")


# Checks
if(BUILD_COVERAGE)
    if(NOT BUILD_TESTS)
        message(FATAL_ERROR "Cannot build coverage without tests, set BUILD_TESTS to ON")
    endif()
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
    endif()
endif()


# Dependencies
find_package(Armadillo ${ARMA_MINIMUM_VERSION} REQUIRED NO_CMAKE_SYSTEM_PATH)
find_package(Fgt 0.1.0 REQUIRED)


# Includes and targets
include(configure_target)
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
configure_package_config_file(
    cmake/CpdConfig.cmake.in
    ${PROJECT_BINARY_DIR}/CpdConfig.cmake
    INSTALL_DESTINATION lib/cpd/cmake
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/CpdConfigVersion.cmake
    VERSION ${CPD_VERSION}
    COMPATIBILITY SameMajorVersion
    )
install(
    FILES
    ${PROJECT_BINARY_DIR}/CpdConfig.cmake
    ${PROJECT_BINARY_DIR}/CpdConfigVersion.cmake
    DESTINATION
    lib/cpd/cmake
    )
install(
    EXPORT CpdTargets
    NAMESPACE Cpd::
    DESTINATION lib/cpd/cmake
    )
