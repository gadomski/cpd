function(cpd_test target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target}
        PRIVATE
        ${GTEST_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}
        )
    target_link_libraries(${target}
        PRIVATE
        gtest_main
        Library-C++
        )
    add_test(NAME ${target} COMMAND ${target})
endfunction()

configure_file(support.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/support.hpp
    )

cpd_test(nonrigid nonrigid_test.cpp)
cpd_test(normalization normalization_test.cpp)
cpd_test(registration registration_test.cpp)
cpd_test(rigid rigid_test.cpp)
cpd_test(utils utils_test.cpp)
