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

#pragma once


namespace fgt {


inline int nchoosek(int n, int k) {
    int n_k = n - k;
    if (k < n_k) {
        k = n_k;
        n_k = n - k;
    }

    int nchsk = 1;
    for (int i = 1; i <= n_k; ++i) {
        nchsk *= ++k;
        nchsk /= i;
    }

    return nchsk;
}
}
