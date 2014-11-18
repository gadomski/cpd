include_directories(
    ${CPD_INCLUDE_DIR}
    ${gtest_SOURCE_DIR}/include
    )

set(SRC
    registration/nonrigid_test.cpp
    )

set(CPD_TEST_LINK_LIBRARIES
    ${CPD_TARGET_LIB}
    gtest_main
    )

add_executable(${CPD_TEST_TARGET} ${SRC})
target_link_libraries(${CPD_TEST_TARGET} ${CPD_TEST_LINK_LIBRARIES})
