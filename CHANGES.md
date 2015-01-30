# Changes

A summary of the changes contained in each version, in reverse chronological order.


#### v0.2.1

- [FIXED] gflags integration
- [FIXED] minor documentation fixes
- [CHANGED] armadillo version used on Travis
- [ADDED] USE_ARMA_WRAPPER option to (optionally) remove armadillo library dependency
- [ADDED] minimum armadillo version


### v0.2.0

- [FIXED] `version.cpp` wasn't adding any symbols to library, this is now fixed
- [FIXED] Our coveralls integration was broken
- [FIXED] Include <memory> in registration.hpp
- [FIXED] Included <armadillo> in defaults.hpp
- [FIXED] Explicitly checkout master when building figtree on Travis
- [FIXED] Detect nonzero return codes in Travis scripts
- [FIXED] Cleaned up CMakeLists.txt
- [FIXED] General code styling
- [CHANGED] Our required CMake version was increased to 2.8.12
- [CHANGED] Rename Registration's `operator()` to `run`
- [CHANGED] Defaults (e.g. DEFAULT_TOLERACE) were changed from UPPER_CASE to CamelCase
- [CHANGED] Rename `SpResult` to `ResultPtr`
- [CHANGED] Moved `Normalization` and `Result` structs inside `Registration`
- [CHANGED] Mechanics of output printing from the command line application
- [CHANGED] Do not use different names for the cpd library when using 32 or 64 bit arma words
- [CHANGED] Use target_compile_definitions to ensure consistent ARMA_64BIT_WORD
- [ADDED] Installation of CPDConfig.cmake and friends for easy downstream project configuration
- [ADDED] Example project demonstrating the usage of CPD in a downstream project
- [ADDED] Allow configuration of sigma2 to improve time and result performance
- [ADDED] CTest support
- [ADDED] Performance test that can be manually used to track regressions in performance on moderately large datasets
- [ADDED] Option to enable/disable deltas in command line output
- [ADDED] Rigid and nonrigid registration to the command line application
- [ADDED] Tests for exceptions


#### v0.1.1

- [FIXED] Critical bug in rigid registration
- [ADDED] Automatic library versioning via git-describe
- [ADDED] `version.cpp` for inspecting the current git version in code
