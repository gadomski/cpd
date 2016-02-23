#!/usr/bin/env sh
# Installs a pre-built cmake

set -ex

wget https://github.com/Viq111/travis-container-packets/releases/download/cmake-2.8.12/cmake.tar.bz2
tar xjf cmake.tar.bz2
rm cmake.tar.bz2
