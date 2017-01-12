#!/usr/bin/env sh
# Installs a pre-built cmake

set -ex

wget https://github.com/Viq111/travis-container-packets/releases/download/cmake-3.1.2/cmake.tar.bz2
tar xjf cmake.tar.bz2
rm cmake.tar.bz2
