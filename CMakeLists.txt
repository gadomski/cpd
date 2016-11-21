cmake_minimum_required(VERSION 2.8.12)
set(CPD_LANGUAGES CXX C)
set(CPD_VERSION 0.4.2)
set(CPD_SOVERSION 0)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Policies
if(POLICY CMP0048) # Project version
    cmake_policy(SET CMP0048 NEW)
    project(cpd LANGUAGES ${CPD_LANGUAGES} VERSION ${CPD_VERSION})
else()
    project(cpd ${CPD_LANGUAGES})
endif()

if(POLICY CMP0042) # MACOSX_RPATH
    cmake_policy(SET CMP0042 NEW)
endif()

if(POLICY CMP0054) # Quoted variables in if statements
    cmake_policy(SET CMP0054 NEW)
endif()

# Depdencies
find_package(Fgt QUIET)
option(WITH_FGT "Build with libfgt" ${Fgt_FOUND})
if(WITH_FGT)
    find_package(Fgt REQUIRED)
else()
    find_package(Eigen3 REQUIRED)
endif()

# Configuration
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
else()
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif()

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/cmake/cpd-config-version.cmake" VERSION ${CPD_VERSION} COMPATIBILITY AnyNewerVersion)
install(FILES cmake/cpd-config.cmake "${PROJECT_BINARY_DIR}/cmake/cpd-config-version.cmake" DESTINATION lib/cmake/cpd)
configure_file(src/version.cpp.in "${PROJECT_BINARY_DIR}/src/version.cpp")

# Targets
set(library_headers
    include/cpd/comparer/direct.hpp
    include/cpd/logging.hpp
    include/cpd/matrix.hpp
    include/cpd/nonrigid.hpp
    include/cpd/normalize.hpp
    include/cpd/probabilities.hpp
    include/cpd/rigid.hpp
    include/cpd/runner.hpp
    include/cpd/utils.hpp
    include/cpd/version.hpp
    )
set(library_src
    src/affinity.cpp
    src/comparer/direct.cpp
    src/nonrigid.cpp
    src/normalize.cpp
    src/rigid.cpp
    src/utils.cpp
    "${PROJECT_BINARY_DIR}/src/version.cpp"
    )
if(WITH_FGT)
    list(APPEND library_headers include/cpd/comparer/fgt.hpp)
    list(APPEND library_src src/comparer/fgt.cpp)
endif()

add_library(Library-C++ ${library_src})
set_target_properties(Library-C++ PROPERTIES
    OUTPUT_NAME cpd
    VERSION ${CPD_VERSION}
    SOVERSION ${CPD_SOVERSION}
    )
target_include_directories(Library-C++
    INTERFACE $<INSTALL_INTERFACE:include> $<INSTALL_INTERFACE:include/cpd/vendor>
    PRIVATE include include/cpd/vendor)
if(WITH_FGT)
    target_link_libraries(Library-C++ PUBLIC Fgt::Library-C++)
    target_compile_definitions(Library-C++ PUBLIC CPD_WITH_FGT)
else()
    target_include_directories(Library-C++ PUBLIC ${EIGEN3_INCLUDE_DIR})
    target_compile_options(Library-C++ PUBLIC -std=c++11)
endif()

option(WITH_STRICT_WARNINGS "Build with stricter warnings" ON)
if(WITH_STRICT_WARNINGS)
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(Library-C++ PRIVATE -Wall -pedantic -Wno-gnu-zero-variadic-macro-arguments)
    endif()
endif()

install(TARGETS Library-C++ DESTINATION lib EXPORT cpd-targets)
install(FILES ${library_headers} DESTINATION include/cpd)
install(DIRECTORY include/cpd/vendor DESTINATION include/cpd)
install(EXPORT cpd-targets NAMESPACE Cpd:: DESTINATION lib/cmake/cpd)

# Optional targets
option(WITH_TESTS "Build test suite" ON)
if(WITH_TESTS)
    enable_testing()
    set(GOOGLETEST_DIR "${PROJECT_SOURCE_DIR}/vendor/googletest-release-1.8.0/googletest")
    add_subdirectory(${GOOGLETEST_DIR})
    add_subdirectory(test)
endif()

find_package(Doxygen QUIET)
option(WITH_DOCS "Add documentation target" ${Doxygen_FOUND})
if(WITH_DOCS)
    find_package(Doxygen REQUIRED)
    configure_file(docs/Doxyfile.in "${PROJECT_BINARY_DIR}/docs/Doxyfile")
    add_custom_target(docs COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_BINARY_DIR}/docs/Doxyfile")
endif()
