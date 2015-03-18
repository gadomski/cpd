configure_file(
    version.cpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
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

add_library(Library ${src})
configure_target(Library)
set_target_properties(Library PROPERTIES
    OUTPUT_NAME cpd
    VERSION ${CPD_VERSION}
    SOVERSION ${CPD_SOVERSION}
    )
target_include_directories(Library
    PUBLIC
    ${ARMADILLO_INCLUDE_DIRS}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    )
target_link_libraries(Library
    PUBLIC
    armadillo
    PRIVATE
    Fgt::Library
    )
install(TARGETS Library
    EXPORT CpdTargets
    INCLUDES DESTINATION include
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
