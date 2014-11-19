if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
fi

mkdir build
cd build
cmake .. -DBUILD_TESTS=true
make
bin/cpd-test
