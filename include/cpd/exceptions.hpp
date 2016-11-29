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

/// \file
/// Exceptions.

#pragma once

namespace cpd {

/// Base class for all cpd errors.
class cpd_error : public std::runtime_error {
public:
    cpd_error(const std::string& what)
      : std::runtime_error(what) {}
};

/// The requested comparer is unknown.
class unknown_comparer : public cpd_error {
public:
    unknown_comparer(const std::string& name)
      : cpd_error(name) {}
};
}
