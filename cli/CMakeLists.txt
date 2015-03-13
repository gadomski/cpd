find_package(gflags 2.1.1 REQUIRED)

option(USE_GFLAGS_SHARED "Build against shared gflags library instead of static" OFF)
option(USE_GFLAGS_THREADED "Build against threaded gflags library instead of non-threaded" ON)

if(USE_GFLAGS_SHARED)
    if(USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags-shared)
    else()
        set(GFLAGS_TARGET gflags_nothreads-shared)
    endif()
else()
    if(USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags-static)
    else()
        set(GFLAGS_TARGET gflags_nothreads-static)
    endif()
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${ARMADILLO_INCLUDE_DIRS}
    ${GFLAGS_INCLUDE_DIR}
    )

set(SRC
    cpd.cpp
    )

add_executable(cpd-cli ${SRC})
cpd_configure_target(cpd-cli NAME cpd EXTRA_COMPILE_FLAGS "-w")
target_link_libraries(cpd-cli
    cpd-lib
    ${GFLAGS_TARGET}
    )
install(TARGETS cpd-cli
    DESTINATION bin
    )
