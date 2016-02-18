configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
    )

set(src
    affinity_eigenvectors_test.cpp
    affinity_matrix_test.cpp
    config.cpp
    exceptions_test.cpp
    find_P_test.cpp
    nonrigid_lowrank_test.cpp
    nonrigid_test.cpp
    rigid_test.cpp
    sigma2_test.cpp
    version_test.cpp

    issues/41-rigid-transformation.cpp
    )

if(ARMA_64BIT_WORD)
    set(src ${src} arma_64bit_test.cpp)
else()
    set(src ${src} arma_32bit_test.cpp)
endif()

add_executable(Test ${src})
configure_target(Test)
# Armadillo accesses `mem_local` on a matrix before initializing the base class,
# which trips this warning in clang 3.6 and *not* on some other compilers.
target_compile_options(Test
	PRIVATE -Wno-uninitialized
	)
set_target_properties(Test PROPERTIES
    OUTPUT_NAME cpd-test
    )
target_compile_options(Test PRIVATE -Wno-uninitialized)
target_include_directories(Test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${ARMADILLO_INCLUDE_DIRS}
    ${gtest_SOURCE_DIR}/include
    )
target_link_libraries(Test
    PRIVATE
    Library
    gtest_main
    )
add_test(NAME unit-tests COMMAND Test)

add_subdirectory(performance)
