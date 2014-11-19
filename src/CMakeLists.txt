include_directories(${CPD_INCLUDE_DIR})

set(SRC
    affinity_matrix.cpp
    find_P.cpp
    sigma2.cpp

    registration/base.cpp
    registration/nonrigid.cpp
    registration/rigid.cpp
    )

add_library(${CPD_LIB_TARGET} ${SRC})
target_link_libraries(${CPD_LIB_TARGET}
    ${ARMADILLO_LIBRARIES}
    ${FIGTREE_LIBRARY}
    )
