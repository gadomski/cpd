#!/usr/bin/env sh
# Installs jsoncpp to $HOME/local

set -ex

wget https://github.com/open-source-parsers/jsoncpp/archive/1.8.0.tar.gz
tar xzf 1.8.0.tar.gz
rm 1.8.0.tar.gz
cd jsoncpp-1.8.0
mkdir build
cd build
cmake .. \
    -DCMAKE_INSTALL_PREFIX=$HOME/local \
    -DBUILD_SHARED_LIBS=ON \
    -DJSONCPP_WITH_CMAKE_PACKAGE=ON \
    -DJSONCPP_WITH_TESTS=OFF \
    -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
make install
