configure_file(support.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/support.hpp")

find_package(Threads)

function(cpd_test name)
    set(src ${name}.cpp)
    string(REPLACE "/" "-" name ${name})
    set(target ${name}-test)
    add_executable(${target} ${src})
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${name})
    add_test(NAME ${name} COMMAND ${target})
    target_link_libraries(${target} PRIVATE Library-C++ gtest_main)
    target_include_directories(${target} PRIVATE
        "${GOOGLETEST_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/cpd/vendor"
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

    if(CMAKE_USE_PTHREADS_INIT)
        target_link_libraries(${target} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
    endif()
endfunction()

cpd_test(affinity_matrix)
cpd_test(comparer/direct)
if(WITH_FGT)
    cpd_test(comparer/fgt)
endif()
cpd_test(nonrigid)
cpd_test(normalize)
cpd_test(rigid)
cpd_test(utils)
cpd_test(version)
