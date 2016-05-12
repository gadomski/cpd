# Style guide

Arbitrary guidelines that I use to keep my anal-rententive tendencies at bay.

## Indenting, whitespace, and such

`.clang-format`

## Documentation

Only public header files need to be documented (Doxygen).
Use `ninja -C build docs` to build them.
Docs are automatically pushed to http://gadomski.github.io/cpd by Travis.

All header files should have a `/// \file filename.hpp` documentation line.

## License

All `cpp` and `hpp` files should have the following preamble:

```
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
```

## Includes

`#include` order goes like this, with exactly one blank line between each category:

1. Standard library, w/ angle brackets.
2. Third-party dependencies (e.g. Eigen) with angle brackets.
3. CPD public headers (e.g. `cpd/rigid.hpp`) with angle brackets.
4. CPD private headers (e.g. `utils.hpp`) with quotes.

Of course, filenames should be alphabetical within category.
