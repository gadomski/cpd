if [[ "$CPD_64BIT" = true ]]
then
    BUILD_64BIT=ON
else
    BUILD_64BIT=OFF
fi

if [[ "$CPD_USE_ARMA_WRAPPER" = true ]]
then
    USE_ARMA_WRAPPER=ON
else
    USE_ARMA_WRAPPER=OFF
fi

mkdir build && cd build
cmake .. \
        -DBUILD_TESTS=ON \
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_64BIT=$BUILD_64BIT \
        -DBUILD_COVERAGE=$CPD_BUILD_COVERAGE \
        -DUSE_ARMA_WRAPPER=$USE_ARMA_WRAPPER && \
    make && \
    bin/cpd-test && \
    sudo make install
