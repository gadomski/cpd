if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
fi

mkdir build
cd build
cmake .. -DBUILD_TESTS=true -DBUILD_CLI=true -DCMAKE_BUILD_TYPE=Release
make
bin/cpd-test
sudo make install
