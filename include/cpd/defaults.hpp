/******************************************************************************
* Coherent Point Drift
* Copyright (C) 2014 Pete Gadomski <pete.gadomski@gmail.com>
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#pragma once

namespace cpd
{
namespace registration
{


// Common
const float DEFAULT_TOLERANCE = 1e-5;
const int DEFAULT_MAX_ITERATIONS = 150;
const float DEFAULT_OUTLIERS = 0.1;
const bool DEFAULT_FGT = true;
const float DEFAULT_EPSILON = 1e-4;
const float DEFAULT_Z_EXAGGERATION = 1.0f;
const bool DEFAULT_AUTO_Z_EXAGGERATION = false;

// Rigid
const bool DEFAULT_STRICT_ROTATION = true;
const bool DEFAULT_USE_SCALING = true;

// Nonrigid
const float DEFAULT_BETA = 2;
const float DEFAULT_LAMBDA = 3;

// NonrigidLowrank
const arma::uword DEFAULT_NUMEIG = 0;


}


}
