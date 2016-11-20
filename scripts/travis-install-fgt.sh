#!/usr/bin/env sh
# Installs fgt to $HOME/local

set -ex

git clone https://github.com/gadomski/fgt.git
mkdir fgt/build
cd fgt/build
cmake .. \
    -DCMAKE_INSTALL_PREFIX=$HOME/local \
    -DWITH_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON
make
make install
