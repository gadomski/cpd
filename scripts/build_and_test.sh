if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
fi

if [[ "$CPD_64BIT" = true ]]
then
    BUILD_64BIT=ON
else
    BUILD_64BIT=OFF
fi

mkdir build
cd build
cmake .. -DBUILD_TESTS=true -DCMAKE_BUILD_TYPE=Release -DBUILD_64BIT=$BUILD_64BIT
make
bin/cpd-test
sudo make install
