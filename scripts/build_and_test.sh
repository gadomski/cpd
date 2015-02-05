if [[ "$CPD_64BIT" = true ]]
then
    BUILD_64BIT=ON
else
    BUILD_64BIT=OFF
fi

mkdir build && cd build
cmake .. \
        -DBUILD_TESTS=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_CLI=ON \
        -DBUILD_64BIT=$BUILD_64BIT \
        -DBUILD_COVERAGE=$CPD_BUILD_COVERAGE && \
    make && \
    bin/cpd-test && \
    sudo make install && \
    /usr/local/bin/cpd
