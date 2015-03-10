set(src
    clustering.cpp
    constant_series.cpp
    direct.cpp
    direct_tree.cpp
    fgt.cpp
    gaussian_transform.cpp
    ifgt.cpp
    monomials.cpp
    truncation_number.cpp
    )

set(deps
    ${ARMADILLO_LIBRARIES}
    )

set(public_compile_defs
    ARMA_64BIT_WORD
    )

if (ARMA_NO_DEBUG)
    list(APPEND public_compile_defs ARMA_NO_DEBUG)
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${ARMADILLO_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/vendor/nanoflann-v1.1.8-25-g6c91a0e/include
    )

add_library(${FGT_LIB_TARGET} ${src})
target_link_libraries(${FGT_LIB_TARGET} ${deps})
set_target_properties(${FGT_LIB_TARGET} PROPERTIES
    OUTPUT_NAME ${FGT_LIB_NAME}
    VERSION ${FGT_VERSION}
    SOVERSION ${FGT_SOVERSION})
target_compile_definitions(${FGT_LIB_TARGET} PUBLIC ${public_compile_defs})

install(
    TARGETS ${FGT_LIB_TARGET}
    EXPORT ${FGT_EXPORT}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
