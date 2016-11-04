cmake_minimum_required(VERSION 2.8.12)
set(CPD_LANGUAGES CXX C)
set(CPD_VERSION 0.4.0)
set(CPD_SOVERSION 0)

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
find_package(Fgt REQUIRED)

# Configuration
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/cmake/cpd-config-version.cmake" VERSION ${CPD_VERSION} COMPATIBILITY AnyNewerVersion)
install(FILES cmake/cpd-config.cmake "${PROJECT_BINARY_DIR}/cmake/cpd-config-version.cmake" DESTINATION lib/cmake/cpd)
configure_file(src/version.cpp.in "${PROJECT_BINARY_DIR}/src/version.cpp")

option(WITH_STRICT_WARNINGS "Build with stricter warnings" ON)
if(WITH_STRICT_WARNINGS)
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wno-gnu-zero-variadic-macro-arguments")
    endif()
endif()

# Targets
set(library_src
    src/affinity_matrix.cpp
    src/comparer.cpp
    src/nonrigid.cpp
    src/normalize.cpp
    src/rigid.cpp
    src/utils.cpp
    "${PROJECT_BINARY_DIR}/src/version.cpp"
    )
add_library(Library-C++ ${library_src})
set_target_properties(Library-C++ PROPERTIES
    OUTPUT_NAME cpd
    VERSION ${CPD_VERSION}
    SOVERSION ${CPD_SOVERSION}
    )
target_link_libraries(Library-C++ PUBLIC Fgt::Library-C++)
target_include_directories(Library-C++
    INTERFACE $<INSTALL_INTERFACE:include> $<INSTALL_INTERFACE:include/cpd/vendor>
    PRIVATE include include/cpd/vendor)
install(TARGETS Library-C++ DESTINATION lib EXPORT cpd-targets)
install(DIRECTORY include/cpd DESTINATION include)
install(EXPORT cpd-targets NAMESPACE Cpd:: DESTINATION lib/cmake/cpd)

# Optional targets
option(WITH_TESTS "Build test suite" ON)
if(WITH_TESTS)
    enable_testing()
    set(GOOGLETEST_DIR "${PROJECT_SOURCE_DIR}/vendor/googletest-release-1.8.0/googletest")
    add_subdirectory(test)
endif()

option(WITH_DOCS "Build documentation" OFF)
if(WITH_DOCS)
    configure_file(Doxyfile.in "${PROJECT_BINARY_DIR}/Doxyfile")
    add_custom_target(docs COMMAND doxygen "${PROJECT_BINARY_DIR}/Doxyfile")
endif()
