configure_file(
    version.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPD_INCLUDE_DIR}
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
    ${FIGTREE_LIBRARY}
    )

if(USE_ARMA_WRAPPER)
    list(APPEND deps ${ARMADILLO_LIBRARIES})
else()
    list(APPEND deps ${ARPACK_LIBRARY})
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        list(APPEND deps ${ACCELERATE_LIBRARY})
    else()
        list(APPEND deps ${LAPACK_LIBRARIES} ${BLAS_LIBRARIES})
    endif()
endif()

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
