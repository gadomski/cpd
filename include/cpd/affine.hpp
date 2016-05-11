// cpd - Coherent Point Drift
// Copyright (C) 2016 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file affine.hpp
/// \brief Affine CPD registration.

#pragma once

#include <cpd/rigid.hpp>

namespace cpd {

/// Affine registration.
class Affine : public Rigid {
private:
    virtual RigidResult compute_impl(const MatrixRef source,
                                     const MatrixRef target, double sigma2);
};

/// Runs affine CPD on two data sets, using all default parameters.
RigidResult affine(const MatrixRef source, const MatrixRef target);

/// Runs affine CPD with the provided sigma2.
RigidResult affine(const MatrixRef source, const MatrixRef target,
                   double sigma2);
}
