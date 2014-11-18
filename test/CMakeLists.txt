include_directories(
    ${CPD_INCLUDE}
    ${gtest_SOURCE_DIR}/include
    )

set(SRC
    )

set(CPD_TEST_LINK_LIBRARIES
    ${CPD_TARGET_LIB}
    gtest_main
    )

add_executable(${CPD_TARGET_TEST} ${SRC})
target_link_libraries(${CPD_TARGET_TEST} ${CPD_TEST_LINK_LIBRARIES})
