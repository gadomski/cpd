#!/usr/bin/env sh
# Travis's build and test script

set -ex

home=$(pwd)

mkdir build
cd build
cmake .. \
    -DWITH_TESTS=ON \
    -DWITH_DOCS=ON \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${home}/local
make
CTEST_OUTPUT_ON_FAIULRE=1 make test
make install
