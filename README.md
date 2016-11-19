# cpd

**Coherent Point Drift (CPD)** is a point-set registration algorithm, originally developed by [Andriy Myronenko](https://sites.google.com/site/myronenko/research/cpd) et al.
This is a C++ library that runs CPD.

CPD can be compared to [Iterative Closest Point](https://en.wikipedia.org/wiki/Iterative_closest_point), another point-set registration algorithm that is widely used.
While ICP minimizes point-to-point distances, CPD uses a [Gaussian Mixture Model](https://en.wikipedia.org/wiki/Mixture_model) to minimize the error between a point and *all other points*.
If you're thinking that this is very computationally intensive, you're right — both the CPD algorithm and the underlying error calculations take a lot of time, which is why we've created [fgt](https://github.com/gadomski/fgt) to speed up those Gauss transforms.
We hope this library provides a freer and more performant alternative to the original reference Matlab implementation.

This library supports two variants of CPD:

- **rigid**: Uses a rigid transformation (i.e. rotation and translation, with an optional scaling) to align the two datasets.
- **nonrigid**: Uses a two-parameter non-rigid transformation function to align the two datasets.

Andriy's reference implementation comes with two other type of registrations, **affine** and **nonrigid_lowrank**, which are not implemented in the latest version of this library (yet) (see [History](#history) for information on how to find and use a previous version of this library that has **nonrigid_lowrank** and **affine**).

This code lives [on Github](https://github.com/gadomski/cpd).
It has some [Doxygen documentation](http://gadomski.github.io/cpd) and is tested [by Travis](https://travis-ci.org/gadomski/cpd) and [by AppVeyor](https://ci.appveyor.com/project/gadomski/cpd/branch/master).
We also have a [gitter chatroom](https://gitter.im/gadomski/cpd).

![Build Status](https://travis-ci.org/gadomski/cpd.svg?branch=master)
![Build status](https://ci.appveyor.com/api/projects/status/iktu9w7gt5bkb63p/branch/master?svg=true)

## Usage

Basic, default usage can be accomplished via some namespace-level methods:

```cpp
#include <cpd/rigid.hpp>

int main(int argc, char** argv) {
    cpd::Matrix fixed = load_points_from_somewhere();
    cpd::Matrix moving = load_points_from_somewhere();
    cpd::Rigid::Result result = cpd::rigid(fixed, moving);
}
```

More advanced configuration can be accomplished by using a `Runner`:

```cpp
#include <cpd/comparer.hpp>
#include <cpd/rigid.hpp>
#include <cpd/runner.hpp>

int main(int argc, char** argv) {
    cpd::Matrix fixed = load_points_from_somewhere();
    cpd::Matrix moving = load_points_from_somewhere();
    cpd::Runner<cpd::Rigid, cpd::FgtComparer> runner;
    runner.correspondence(true).outliers(0.2);
    cpd::Rigid::Result result = runner.run(fixed, moving);
}
```

See the code and the [documentation](http://gadomski.github.io/cpd) to discover all possible options, transformation methods, and probability calculation methods.

## Examples

See `examples/` in this code repository for some basic usage examples, including examples of how to set up a downstream CMake project that depends on cpd.

## Installation

**cpd** depends on and [CMake](https://cmake.org/) and [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) at build time only — no runtime dependencies.
For additional speed, it can also built with [fgt](https://github.com/gadomski/fgt).

### On OSX

If you're on a Mac, use [homebrew](http://brew.sh/) and [my tap](https://github.com/gadomski/homebrew-gadomski) to install:

```bash
brew tap gadomski/gadomski
brew install cpd
```

### From source

Use the usual CMake build incantation:

```bash
mkdir build
cd build
cmake ..
make
```

### Using downstream

**cpd** provides CMake export targets that you can import and use in your own project:

```cmake
find_package(Cpd REQUIRED)
add_library(my-great-library
    the_code.cpp
    )
target_link_libraries(my-great-library
    PUBLIC
    Cpd::Library-C++
    )
```

The `Cpd::Library-C++` target includes all the interface settings you need, so you shouldn't need any other calls to get set up.

## OpenMP

Both fgt and Eigen support OpenMP for some operations.
As of yet, the interaction between the two is untested, so our official recommendation is to only use OpenMP with one of the projects, not both.
If you do some work with OpenMP we'd love to hear how it goes.

## Contributing

Github [issues](https://github.com/gadomski/cpd/issues) and [pull requests](https://github.com/gadomski/cpd/pulls), per usual.

## History

The [v0.1](https://github.com/gadomski/cpd/tree/v0.1) and [v0.2](https://github.com/gadomski/cpd/tree/v0.2) lineages of **cpd** used [armadillo](http://arma.sourceforge.net/) for linear arithmetic instead of Eigen.
Armadillo is a bit smoother for doing advanced eigenvalue decompositions and other operations, which made it a bit easier at first to directly port the Matlab reference implementation.
For a couple of reasons, we decided to switch to Eigen for v0.3.

First, the Armadillo project had the bad habit of removing old versions from their download site, making it hard to maintain working code as their codebase developed.
Second, many downstream applications use Eigen themselves, making Eigen a lower-friction choice for those users.

As of this writing, the Eigen implementation is less feature-full than the old Armadillo implementation, particularly with respect to the nonrigid_lowrank version.
If you require some of that old functionality, use the [v0.2](https://github.com/gadomski/cpd/tree/v0.2) branch.
If you need armadillo-5.x, which is required for the old **cpd** but is no longer available from the armadillo website, you can use [my mirror](https://github.com/gadomski/armadillo).
Thanks for your understanding during this switch.

## License

This library is GPL2, copyright 2016 Peter J. Gadomski.
See LICENSE.txt for the full license text.

This work is directly inspired by Andriy Myronenko's reference implementation, and we owe him many thanks.
