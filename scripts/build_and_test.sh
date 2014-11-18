mkdir build
cd build
cmake .. -DBUILD_TESTS=true
make
./cpd-test
