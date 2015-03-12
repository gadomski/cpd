configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
    )

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${ARMADILLO_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${gtest_SOURCE_DIR}/include
    )

set(src
    config.cpp

    affinity_eigenvectors_test.cpp
    affinity_matrix_test.cpp
    exceptions_test.cpp
    find_P_test.cpp
    nonrigid_lowrank_test.cpp
    nonrigid_test.cpp
    rigid_test.cpp
    sigma2_test.cpp
    version_test.cpp
    )

if(ARMA_64BIT_WORD)
    set(src ${src} arma_64bit_test.cpp)
else()
    set(src ${src} arma_32bit_test.cpp)
endif()

set(deps
    cpd-lib
    gtest_main
    )

add_executable(cpd-test ${src})
target_link_libraries(cpd-test ${deps})
cpd_configure_target(cpd-test EXTRA_COMPILE_FLAGS "-w")
add_test(unit-tests ${PROJECT_BINARY_DIR}/bin/cpd-test)

if(BUILD_COVERAGE)
    add_custom_target(cpd-coverage
        COMMAND bin/cpd-test
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating code coverage"
        )
    cpd_configure_target(cpd-coverage)
endif()

add_subdirectory(performance)
