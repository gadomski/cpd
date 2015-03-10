// fgt, C++ library for Fast Gauss Transforms
// Copyright (C) 2015 Peter J. Gadomski <pete.gadomski@gmail.com>
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

#include <fgt/fgt.hpp>

#include <cassert>


namespace fgt {


namespace {
// This value was arrived at through two avenues:
//
// 1. It is given as a rough rule of thumb in Raykar, V. C., Yang, C., &
// Duraiswami, R. (2006). Improved fast Gauss transform User manual
//
// 2. It was roughly the break point in developer testing of figtree
// (https://github.com/vmorariu/figtree) on some user data. Very emperical, but
// since it lined up with the rule of thumb, we accepted it as a useful value.
//
// figtree, on which this library is based, does some back of the envelope flop
// guesses for each run, which seems like complexity we would like to avoid if
// at all possible. It is conceivable down the road that we could either
// implement similar flop guessing, or do some per-machine tuning ala ATLAS,
// but for now let's kiss.
static const double IfgtToDirectTreeBandwithBreakpoint = 1e-1;
}


std::unique_ptr<GaussTransform>
choose_gaussian_transform(const arma::mat& source, double bandwidth,
                          double epsilon) {
    if (bandwidth < IfgtToDirectTreeBandwithBreakpoint) {
        return std::unique_ptr<GaussTransform>(
            new DirectTree(source, bandwidth, epsilon));
    } else {
        return std::unique_ptr<GaussTransform>(
            new Ifgt(source, bandwidth, epsilon));
    }
    assert(false && "Unreachable code");
}
}
