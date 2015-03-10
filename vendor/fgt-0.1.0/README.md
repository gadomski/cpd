# fgt

**fgt** is an LGPL C++ library for quickly performing [Gauss transforms](https://en.wikipedia.org/wiki/Weierstrass_transform).
**fgt** can do an Improved Fast Gauss Transform, a direct Gauss transform using an approximate nearest neighbor simplification, and the direct Gauss transform.
This library is heavily based on previous work in the [figtree](https://github.com/vmorariu/figtree) library, as well as the original [Improved Fast Gauss Transform](http://www.umiacs.umd.edu/labs/cvl/pirl/vikas/Software/IFGT/IFGT_code.htm) code.

[![Build Status](https://travis-ci.org/gadomski/fgt.svg?branch=master)](https://travis-ci.org/gadomski/fgt)


## Usage

Let **fgt** pick the best Gauss transform for your purposes:

```cpp
GaussTransformUnqPtr transfom = choose_gauss_transform(source, bandwidth, epsilon);
auto transform = transform->compute(target, weights);
```

Run the Improved Fast Gauss Transform:

```cpp
Ifgt ifgt = Ifgt(source, bandwidth, epsilon);
auto transform = ifgt.compute(target, weights);
```

## Dependencies


**fgt** requires a modern compiler that supports many c++11 features, such as clang 3.4 or gcc 4.8, and [armadillo](http://arma.sourceforge.net/), a C++ linear algebra library.
On OSX, installing armadillo is easy with [homebrew](http://brew.sh/):

```bash
$ brew install armadillo
```

On Ubuntu:

```bash
$ sudo apt-get install libarmadillo-dev
```

Windoze, caveat emptor.


## Installation

**fgt** uses [CMake](http://www.cmake.org/):

```bash
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
```

**fgt** comes with a CMake configuration file that lets downstream projects easily integrate **fgt** targets.
For example, if **fgt** is installed to a location in the default CMake find package path, you can easily integrate `fgt-lib` into a downstream CMakeLists.txt:

```cmake
find_package(Fgt REQUIRED)
add_executable(my-great-program main.cpp)
target_link_libraries(my-great-program fgt-lib)
```

If you have installed **fgt** to a non-standard location, you may have to set `Fgt_DIR` in your downstream CMake cache.


## A Note Regarding Performance

Armadillo is a template-heavy header library, so relies heavily on optimizations to achieve reasonable performance.
Set `CMAKE_BUILD_TYPE=Release` for good results.

If you are confident in your code, you can also set `ARMA_NO_DEBUG=ON` to disable bounds checks on armadillo matrices.
This opens up your code to problems, but if you're confident, you can get another performance boost by sidestepping those checks.


## License

This software is distributed under the GNU Lesser General Public License v2.1.
A copy of this license can be found in LICENSE.txt.

This version is copyright (c) Peter J. Gadomski <pete.gadomski@gmail.com>.
