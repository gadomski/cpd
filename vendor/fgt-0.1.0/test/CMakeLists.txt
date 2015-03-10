configure_file(
    config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
    )

set(src
    clustering_test.cpp
    constant_series_test.cpp
    direct_test.cpp
    direct_tree_test.cpp
    gaussian_transform_test.cpp
    ifgt_test.cpp
    monomials_test.cpp
    truncation_number_test.cpp
    )

set(deps
    ${FGT_LIB_TARGET}
    gtest_main
    )

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${gtest_SOURCE_DIR}/include
    )

add_executable(${FGT_TEST_TARGET} ${src})
target_link_libraries(${FGT_TEST_TARGET} ${deps})
add_test(unit-tests ${PROJECT_BINARY_DIR}/bin/${FGT_TEST_TARGET})

add_executable(${FGT_TRIAL_TARGET} trial.cpp)
target_link_libraries(${FGT_TRIAL_TARGET} ${deps})
