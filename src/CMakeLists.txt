include_directories(${CPD_INCLUDE_DIR})

set(SRC
    registration/base.cpp
    )

add_library(${CPD_LIB_TARGET} ${SRC})
target_link_libraries(${CPD_LIB_TARGET}
    ${ARMADILLO_LIBRARIES}
    )
