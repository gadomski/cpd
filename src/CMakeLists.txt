include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPD_INCLUDE_DIR}
    )

set(SRC
    affinity_eigenvectors.cpp
    affinity_matrix.cpp
    find_P.cpp
    sigma2.cpp

    registration.cpp
    nonrigid.cpp
    nonrigid_lowrank.cpp
    rigid.cpp
    )

add_library(${CPD_LIB_TARGET} ${SRC})
set_property(TARGET ${CPD_LIB_TARGET} PROPERTY OUTPUT_NAME ${CPD_LIB_NAME})
target_link_libraries(${CPD_LIB_TARGET}
    ${ARMADILLO_LIBRARIES}
    ${FIGTREE_LIBRARY}
    )
install(TARGETS ${CPD_LIB_TARGET}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
