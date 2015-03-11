configure_file(
    version.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
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

add_library(cpd-lib ${src})
target_link_libraries(cpd-lib ${deps})
cpd_configure_target(cpd-lib NAME cpd)
install(TARGETS cpd-lib
    EXPORT ${CPD_EXPORT}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
