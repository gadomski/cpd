function(cpd_test target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target}
        PRIVATE
        ${GTEST_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/cpd/vendor
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}
        )
    target_link_libraries(${target}
        PRIVATE
        gtest_main
        Library-C++
        )
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
        target_compile_options(${target}
            PRIVATE
            # Heap allocated object alignment whatever man
            /wd4316)
    endif()
    add_test(NAME ${target} COMMAND ${target})
endfunction()

configure_file(support.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/support.hpp
    )

cpd_test(affine affine_test.cpp)
cpd_test(nonrigid nonrigid_test.cpp)
cpd_test(normalization normalization_test.cpp)
cpd_test(rigid rigid_test.cpp)
cpd_test(utils utils_test.cpp)
cpd_test(version version_test.cpp)
