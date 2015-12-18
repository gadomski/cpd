# cpd

C++ library for point set registration using the [Coherent Point Drift](https://sites.google.com/site/myronenko/research/cpd) algorithm.
This library is derived from Matlab code written by Andriy Myronenko and is available under the same license (GPL2).

![Registering glacier data](doc/helheim-cpd.gif)

This project provides a library, **libcpd**, for use in your own applications.
It also provides an optional command-line executable, called simply **cpd**, which provides a subset of the library's functionality for quick command-line usage.

[![Build Status](https://travis-ci.org/gadomski/cpd.svg?branch=master)](https://travis-ci.org/gadomski/cpd)
[![Coverage Status](https://img.shields.io/coveralls/gadomski/cpd.svg)](https://coveralls.io/r/gadomski/cpd)


## Usage (C++ API)

The CPD source includes an example project, located in `example/`, that demonstrates a simple usage of the C++ API.
The latest example code is also available at https://github.com/gadomski/cpd/tree/master/example.

If CPD is installed to a non-standard location, you will have to provide the `CPD_DIR` option to cmake.
This directory should point to the location of the cmake configure scripts — these are usually located in the `lib/cpd/cmake` directory underneath the installation prefix.

For example, if I installed cpd with `CMAKE_INSTALL_PREFIX=/home/gadomski/local/`, I would set `CPD_DIR` to `/home/gadomski/local/lib/cpd/cmake`.

If you install CPD to one of the standard library locations (`/usr`, `/usr/local`), CPD's cmake configure scripts should be picked up automatically, and you should not need to set `CPD_DIR`.


## Usage (command-line)

Register two point sets using the nonrigid_lowrank algorithm:

```bash
cpd file1.txt file2.txt > output.txt
```

The input files must be whitespace-delimited files with XYZ values only.
The output file will be whitespace-delimited with the following columns: X, Y, Z, dX, dY, dZ, where dX, dY, and dZ are the change in position in the X, Y, and Z directions respectively for that point.

Run `cpd --help` for a description of the command-line options available for customizing the CPD algorithm.


## System requirements

**cpd** has been tested on the following systems:

- Mac OSX 10.10.1, x86_64-apple-darwin14.0.0
- Ubuntu 12.04 LTS Server Edition 64 bit

And the following compilers:

- Apple LLVM verison 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
- Clang 3.2.x
- GCC 4.8.x


## Installation

**cpd** depends on the following:

- [fgt](https://github.com/gadomski/fgt): C++ library for performing a Fast Gauss Transform
- [armadillo](http://arma.sourceforge.net/): C++ linear algebra library
- [lapack](http://www.netlib.org/lapack/): linear algebra package
- [arpack](http://www.caam.rice.edu/software/ARPACK/): large scale eigenvalue solutions
- [gflags](https://code.google.com/p/gflags/) (optional): commandline flags
  processing, required only if you're building the commandline application

To build **cpd** yourself, you will need all of the above, plus:

- [git](http://git-scm.com/): distributed version control system
- [cmake](http://www.cmake.org/): cross-platform, open-source build system
  (version 2.8.12 or higher required)
- a modern compiler that supports `-std=c++0x`, e.g. gcc-4.8 or a newer clang

Instructions are provided below for installing on Mac OSX and linux.
Windoze, you're on your own.

### Dependencies on Mac OSX

OSX comes with lapack and arpack, so you're all set there.
Most of the rest of the dependencies are available through **homebrew**, a great package manager for OSX.
If you're don't have **homebrew**, [get it](http://brew.sh/).
Then, install stuff:

```bash
brew update
brew install cmake armadillo
```

If you're planning on using the command line application, additionally do:

```bash
brew install gflags
```

Now you're ready to [install cpd](#installing-cpd-on-both-mac-os-x-and-linux).


### Dependencies on Linux

Use apt-get to grab some stuff:

```bash
sudo apt-get update
sudo apt-get install git cmake liblapack-dev libarpack2-dev libsuperlu3-dev gfortran
```

If you have an old gcc, you may need to update it.
See [one of cpd's continuous integration scripts](https://github.com/gadomski/cpd/blob/master/scripts/install_compilers.sh) for one way to update your gcc.

You'll need to install armadillo from source.
Again, you can just follow the scripts: [armadillo](https://github.com/gadomski/cpd/blob/master/scripts/install_armadillo.sh).

Now you're ready to [install cpd](#installing-cpd-on-both-mac-os-x-and-linux).


### Installing fgt and cpd on both Mac OS X and linux

First, install [fgt](https://github.com/gadomski/fgt), following its installation instructions.

Now download and install **cpd**:

```bash
git clone https://github.com/gadomski/cpd.git
mkdir cpd/build && cd cpd/build

# you can omit the -DBUILD_CLI=ON part if you don't need the commandline app
cmake .. -DBUILD_CLI=ON

make
```

To test that things built correctly:

```bash
bin/cpd-test
```

If you want to install **cpd** to system-wide directories:

```bash
make install
```

If you're on a linux or didn't use homebrew on OSX, you may need a `sudo make install`.

If you have problems at any point during the build, please [open a new
issue](https://github.com/gadomski/cpd/issues/new).


## Versioning

**cpd** follows [semantic versioning](http://semver.org/).
In particular, any release with a 0.x.x prefix should be considered initial development, and used with the understanding that anything could change at any time.
However, when in initial development we will do our best to increment the MINOR version when we make big, breaking changes, and notify users accordingly in the release notes.

Releases will be tagged and available [via Github](https://github.com/gadomski/cpd/releases).
The latest release is also available as the [**production** branch](https://github.com/gadomski/cpd/tree/production).
Main development will occur in the [**master** branch](https://github.com/gadomski/cpd/tree/master).


## License

This software is distributed under the terms of the original Matlab implementation.
A complete copy of the GPL2 license can be found in LICENSE.txt of this source tree.
Each source file also contains a brief preamble specifying the license.

This version is copyright (c) 2014 Pete Gadomski <pete.gadomski@gmail.com>.

The original Matlab implementation was copyright (c) 2008-2009 Andriy Myronenko.
His website is here: https://sites.google.com/site/myronenko/home.


## Issues and Contributing

We use github's [issues](https://github.com/gadomski/cpd/issues) and [pull requests](https://github.com/gadomski/cpd/pulls).
Please feel free to contribute either.


## Contributers

This library was developed by [@gadomski](https://github.com/gadomski) with support from the Army Corps of Engineers [Cold Regions Research and Development Lab](https://github.com/CRREL).
