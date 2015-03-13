mkdir build && cd build
cmake .. \
        -DBUILD_TESTS=ON \
        -DCMAKE_BUILD_TYPE=RelWithDebInfo \
        -DBUILD_CLI=ON \
        -DARMA_64BIT_WORD=$ARMA_64BIT_WORD \
        -DBUILD_COVERAGE=$CPD_BUILD_COVERAGE && \
    make && \
    bin/cpd-test && \
    sudo make install && \
    /usr/local/bin/cpd
