#!/usr/bin/env sh
# Travis's build and test script

set -ex

mkdir build
cd build
cmake .. \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/local \
    -DWITH_DOCS=ON \
    -DWITH_FGT=$CPD_WITH_FGT \
    -DWITH_JSONCPP=ON \
    -DWITH_STRICT_WARNINGS=ON \
    -DWITH_TESTS=ON
make
CTEST_OUTPUT_ON_FAIULRE=1 make test
make install
cd ../examples
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=$HOME/local
make
