find_package(gflags REQUIRED)

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
    ${GFLAGS_LIBRARIES}
    )
install(TARGETS ${CPD_CLI_TARGET}
    DESTINATION bin
    )
