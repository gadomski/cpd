# Basic setup
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(fgt CXX C)
set(FGT_VERSION 0.1.0)
set(FGT_SOVERSION 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MACOSX_RPATH ON)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)


# Options
option(BUILD_SHARED_LIBS "Create shared libraries" ON)
option(BUILD_TESTS "Build test suite" ON)
option(ARMA_NO_DEBUG "Build without Armadillo bounds checks" OFF)


# Dependencies
find_package(Armadillo 4.500.1 REQUIRED)


# Targets
set(FGT_LIB_TARGET fgt-lib)
set(FGT_LIB_NAME fgt)
set(FGT_TEST_TARGET fgt-test)
set(FGT_TRIAL_TARGET fgt-trial)
set(FGT_EXPORT FgtTargets)


# Subdirectories
add_subdirectory(include)
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(vendor/gtest-1.7.0)
    add_subdirectory(test)
endif()


# FgtConfig.cmake
include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR include)

configure_package_config_file(
    cmake/FgtConfig.cmake.in
    ${PROJECT_BINARY_DIR}/FgtConfig.cmake
    INSTALL_DESTINATION lib/fgt/cmake
    PATH_VARS INCLUDE_INSTALL_DIR
    )
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/FgtConfigVersion.cmake
    VERSION ${FGT_VERSION}
    COMPATIBILITY SameMajorVersion
    )
export(TARGETS ${FGT_LIB_TARGET} FILE ${PROJECT_BINARY_DIR}/FgtTargets.cmake)

install(
    FILES
        ${PROJECT_BINARY_DIR}/FgtConfig.cmake
        ${PROJECT_BINARY_DIR}/FgtConfigVersion.cmake
    DESTINATION
        lib/fgt/cmake
        )
install(
    EXPORT ${FGT_EXPORT}
    DESTINATION lib/fgt/cmake
    )
