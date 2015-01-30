find_package(gflags 2.1.1 REQUIRED)

option(USE_GFLAGS_SHARED "Build against shared gflags library instead of static" OFF)
option(USE_GFLAGS_THREADED "Build against threaded gflags library instead of non-threaded" ON)

if (USE_GFLAGS_SHARED)
    if (USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags-shared)
    else(USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags_nothreads-shared)
    endif(USE_GFLAGS_THREADED)
else(USE_GFLAGS_SHARED)
    if (USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags-static)
    else(USE_GFLAGS_THREADED)
        set(GFLAGS_TARGET gflags_nothreads-static)
    endif(USE_GFLAGS_THREADED)
endif(USE_GFLAGS_SHARED)

include_directories(
    ${CPD_INCLUDE_DIR}
    ${GFLAGS_INCLUDE_DIR}
    )

set(SRC
    cpd.cpp
    )

add_executable(${CPD_CLI_TARGET} ${SRC})
set_property(TARGET ${CPD_CLI_TARGET} PROPERTY OUTPUT_NAME cpd)
target_link_libraries(${CPD_CLI_TARGET}
    ${CPD_LIB_TARGET}
    ${GFLAGS_TARGET}
    )
install(TARGETS ${CPD_CLI_TARGET}
    DESTINATION bin
    )
