include_directories(
    ${CPD_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )

set(SRC
    find_P_test.cpp
    sigma2_test.cpp

    registration/nonrigid_test.cpp
    registration/rigid_test.cpp
    )

set(CPD_TEST_LINK_LIBRARIES
    ${CPD_LIB_TARGET}
    gtest_main
    )

add_executable(${CPD_TEST_TARGET} ${SRC})
target_link_libraries(${CPD_TEST_TARGET} ${CPD_TEST_LINK_LIBRARIES})
