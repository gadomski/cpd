set(src
    ../config.cpp
    timer.cpp

    nonrigid_lowrank_performance_test.cpp
    rigid_performance_test.cpp
    )

set(deps
    cpd-lib
    gtest_main
    )

add_executable(cpd-performance ${src})
target_link_libraries(cpd-performance ${deps})
cpd_configure_target(cpd-performance EXTRA_COMPILE_FLAGS "-w")
