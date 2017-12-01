project(cpd-examples CXX)
cmake_minimum_required(VERSION 2.8.12)

find_package(Cpd REQUIRED)

if("${CPD_WITH_JSONCPP}")
    find_package(Cpd COMPONENTS jsoncpp)
    add_executable(cpd-rigid rigid.cpp)
    target_link_libraries(cpd-rigid PRIVATE Cpd::Library-C++ Cpd::Jsoncpp)

    if("${Fgt_FOUND}")
        add_executable(cpd-fgt fgt.cpp)
        target_link_libraries(cpd-fgt PRIVATE Cpd::Library-C++ Cpd::Jsoncpp)
    endif()
endif()

add_executable(cpd-version version.cpp)
target_link_libraries(cpd-version PRIVATE Cpd::Library-C++)

add_executable(cpd-random random.cpp)
target_link_libraries(cpd-random PRIVATE Cpd::Library-C++)

add_executable(cpd-callback callback.cpp)
target_link_libraries(cpd-callback PRIVATE Cpd::Library-C++)

add_executable(cpd-transform transform.cpp)
target_link_libraries(cpd-transform PRIVATE Cpd::Library-C++)
