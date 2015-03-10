configure_file(
    version.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPD_INCLUDE_DIR}
    ${ARMADILLO_INCLUDE_DIRS}
    ${FGT_INCLUDE_DIRS}
    )

set(src
    affinity_eigenvectors.cpp
    affinity_matrix.cpp
    find_P.cpp
    nonrigid.cpp
    nonrigid_lowrank.cpp
    registration.cpp
    rigid.cpp
    sigma2.cpp

    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    )

set(deps
    fgt-lib
    ${ARMADILLO_LIBRARIES}
    )

add_library(${CPD_LIB_TARGET} ${src})

set_property(TARGET ${CPD_LIB_TARGET} PROPERTY OUTPUT_NAME ${CPD_LIB_NAME})
set_property(TARGET ${CPD_LIB_TARGET} PROPERTY VERSION ${CPD_VERSION})
set_property(TARGET ${CPD_LIB_TARGET} PROPERTY SOVERSION ${CPD_SOVERSION})

target_link_libraries(${CPD_LIB_TARGET} ${deps})
if(BUILD_64BIT)
    target_compile_definitions(${CPD_LIB_TARGET} PUBLIC ARMA_64BIT_WORD)
endif()


install(TARGETS ${CPD_LIB_TARGET}
    EXPORT ${CPD_EXPORT}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
