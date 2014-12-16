set(src
    ../config.cpp
    timer.cpp

    nonrigid_lowrank_performance_test.cpp
    rigid_performance_test.cpp
    )

set(deps
    ${CPD_LIB_TARGET}
    gtest_main
    )

add_executable(${CPD_PERFORMANCE_TEST_TARGET} ${src})
target_link_libraries(${CPD_PERFORMANCE_TEST_TARGET} ${deps})
