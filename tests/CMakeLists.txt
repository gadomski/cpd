configure_file(support.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/support.hpp")

include(cpd_test)

cpd_test(affine)
cpd_test(gauss_transform)
cpd_test(nonrigid)
cpd_test(normalization)
cpd_test(rigid)
cpd_test(utils)
cpd_test(version)

if(WITH_FGT)
    cpd_test(gauss_transform_fgt)
endif()
