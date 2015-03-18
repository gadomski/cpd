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

set(src
    cpd.cpp
    )

add_executable(Cli ${src})
configure_target(Cli)
set_target_properties(Cli PROPERTIES
    OUTPUT_NAME cpd
    )
target_include_directories(Cli
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    )
target_link_libraries(Cli
    PRIVATE
    Library
    ${GFLAGS_TARGET}
    )
install(TARGETS Cli
    RUNTIME DESTINATION bin
    )
