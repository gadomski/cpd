set(src
    ../config.cpp
    timer.cpp

    nonrigid_lowrank_performance_test.cpp
    rigid_performance_test.cpp
    )

add_executable(Performance ${src})
configure_target(Performance)
set_target_properties(Performance PROPERTIES
    OUTPUT_NAME cpd-performance
    )
target_include_directories(Performance
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test
    ${CMAKE_CURRENT_BINARY_DIR}/..
    ${gtest_SOURCE_DIR}/include
    )
target_link_libraries(Performance
    PRIVATE
    Library
    gtest_main
    )
