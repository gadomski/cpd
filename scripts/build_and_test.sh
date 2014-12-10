if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
    BUILD_COVERAGE=ON
else
    BUILD_COVERAGE=OFF
fi

if [[ "$CPD_64BIT" = true ]]
then
    BUILD_64BIT=ON
else
    BUILD_64BIT=OFF
fi

mkdir build
cd build
cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug -DBUILD_64BIT=$BUILD_64BIT -DBUILD_COVERAGE=$BUILD_COVERAGE
make
bin/cpd-test
sudo make install
cd ..

if [[ "$BUILD_COVERAGE" == "ON" ]]
then
    coveralls \
        --gcov-options '\-lp' \
        -b build/ \
        --gcov /usr/bin/gcov-4.8 \
        --exclude build/vendor/ \
        --exclude build/test/ \
        --exclude figtree-build/ \
        --exclude armadillo-4.500.1/ \
        --exclude figtree/ \
        --exclude test/ \
        --exclude build/CMakeFiles
fi
