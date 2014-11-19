include_directories(${CPD_INCLUDE_DIR})

set(SRC
    affinity_eigenvectors.cpp
    affinity_matrix.cpp
    find_P.cpp
    sigma2.cpp

    registration/base.cpp
    registration/nonrigid.cpp
    registration/nonrigid_lowrank.cpp
    registration/rigid.cpp
    )

add_library(${CPD_LIB_TARGET} ${SRC})
set_property(TARGET ${CPD_LIB_TARGET} PROPERTY OUTPUT_NAME cpd)
target_link_libraries(${CPD_LIB_TARGET}
    ${ARMADILLO_LIBRARIES}
    ${FIGTREE_LIBRARY}
    )
