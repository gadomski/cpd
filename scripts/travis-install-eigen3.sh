#!/usr/bin/env sh
# Installs eigen to $HOME/local

set -ex

home=$(pwd)

wget http://bitbucket.org/eigen/eigen/get/3.2.8.tar.gz
tar xzf 3.2.8.tar.gz
rm 3.2.8.tar.gz
cd eigen-eigen-07105f7124f9
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$home/local
make install
