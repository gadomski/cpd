include_directories(
    ${CPD_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )

set(SRC
    affinity_eigenvectors_test.cpp
    affinity_matrix_test.cpp
    find_P_test.cpp
    sigma2_test.cpp

    nonrigid_test.cpp
    nonrigid_lowrank_test.cpp
    rigid_test.cpp
    )

if (BUILD_64BIT)
    set(SRC ${SRC} arma_64bit_test.cpp)
else()
    set(SRC ${SRC} arma_32bit_test.cpp)
endif (BUILD_64BIT)

set(CPD_TEST_LINK_LIBRARIES
    ${CPD_LIB_TARGET}
    gtest_main
    )

add_executable(${CPD_TEST_TARGET} ${SRC})
target_link_libraries(${CPD_TEST_TARGET} ${CPD_TEST_LINK_LIBRARIES})

if (BUILD_COVERAGE)
    add_custom_target(${CPD_COVERAGE_TARGET}
        COMMAND bin/${CPD_TEST_TARGET}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating code coverage"
        )
endif (BUILD_COVERAGE)
