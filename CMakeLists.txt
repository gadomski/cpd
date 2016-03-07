project(cpd CXX)
cmake_minimum_required(VERSION 2.8.12)

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

set(CPD_VERSION 0.3.1)
set(CPD_SOVERSION 0)
message(STATUS "[cpd] Version: ${CPD_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(GTEST_SOURCE_DIR "${PROJECT_SOURCE_DIR}/vendor/gtest-1.7.0")

option(WITH_TESTS "Build unit tests" ON)

set(FGT_MINIMUM_VERSION 0.4)
find_package(Fgt ${FGT_MINIMUM_VERSION} REQUIRED)
message(STATUS "[cpd] Fgt version: ${Fgt_VERSION}")

add_library(Library-C++
    src/nonrigid.cpp
    src/normalization.cpp
    src/registration.cpp
    src/rigid.cpp
    src/transformer.cpp
    src/utils.cpp
    )
target_include_directories(Library-C++
    INTERFACE
    ${CMAKE_INSTALL_PREFIX}/include
    PRIVATE
    include
    )
target_link_libraries(Library-C++
    PUBLIC
    Fgt::Library-C++
    )
target_compile_options(Library-C++
    PRIVATE
    -pedantic -Wall
    )
set_target_properties(Library-C++ PROPERTIES
    OUTPUT_NAME cpd
    VERSION ${CPD_VERSION}
    SOVERSION ${CPD_SOVERSION}
    )
install(FILES
    include/cpd/matrix.hpp
    include/cpd/normalization.hpp
    include/cpd/nonrigid.hpp
    include/cpd/registration.hpp
    include/cpd/rigid.hpp
    DESTINATION include/cpd
    )
install(TARGETS Library-C++
    DESTINATION lib
    EXPORT cpd-targets
    )

configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
add_custom_target(docs
    COMMAND doxygen ${PROJECT_BINARY_DIR}/Doxyfile
    )

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(${GTEST_SOURCE_DIR})
    set_target_properties(gtest PROPERTIES MACOSX_RPATH ON)
    set_target_properties(gtest_main PROPERTIES MACOSX_RPATH ON)
    add_subdirectory(test)
endif()

include(CMakePackageConfigHelpers)
configure_file(cmake/cpd-config.cmake
    ${PROJECT_BINARY_DIR}/cpd-config.cmake
    @ONLY
    )
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/cpd-config-version.cmake
    VERSION ${CPD_VERSION}
    COMPATIBILITY AnyNewerVersion
    )
install(FILES
    ${PROJECT_BINARY_DIR}/cpd-config.cmake
    ${PROJECT_BINARY_DIR}/cpd-config-version.cmake
    DESTINATION lib/cmake/cpd
    )
install(EXPORT cpd-targets
    DESTINATION lib/cmake/cpd
    NAMESPACE Cpd::
    )
