#!/usr/bin/env sh
# Installs fgt to $HOME/local

set -ex

fgt_version=0.4.2
home=$(pwd)

wget https://github.com/gadomski/fgt/archive/v${fgt_version}.tar.gz
tar xzf v${fgt_version}.tar.gz
rm v${fgt_version}.tar.gz
cd fgt-${fgt_version}
mkdir build
cd build
cmake .. \
    -DCMAKE_INSTALL_PREFIX=$home/local \
    -DWITH_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON
make
make install
