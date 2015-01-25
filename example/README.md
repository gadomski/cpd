Example application using cpd's C++ API
=======================================

This is a small sample application demonstrating usage of cpd's C++ API.
The program constructs a small executable which can read two text files and run a nonrigid registration on the points contained in those files.


Building
--------

To build the example application, you must have CPD and all of its dependencies dependencies installed.
See https://github.com/gadomski/cpd/ for instructions.

Once CPD is installed, navigate to the example folder, then run the following:

```bash
mkdir build
cd build
cmake ..
make
```

This should build the example application in the `build` subdirectory of the example project.
Then, to run the program:

```bash
./cpd-example-project ../X.txt ../Y.txt
```

This will run CPD's nonrigid registration on the two text files included in the example project.
The results will be printed to the standard output stream.
The results of the registration are the X, Y, and Z coordinates of the registered points from the Y dataset, as well as the deltas (change) of each points from its original location.
