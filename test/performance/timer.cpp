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

#include "performance/timer.hpp"

#include <iomanip>


namespace cpd
{
namespace test
{


void Timer::start()
{
    m_c_start = std::clock();
    m_t_start = std::chrono::high_resolution_clock::now();
}


void Timer::end()
{
    m_c_end = std::clock();
    m_t_end = std::chrono::high_resolution_clock::now();
}


std::ostream& operator<<(std::ostream& os, const Timer& timer)
{
    os << std::fixed << std::setprecision(2)
        << "processor time: "
        << timer.clock_time() << " ms"
        << std::endl
        << "wall clock time: "
        << timer.chrono_time()
        << " ms";
    return os;
}


}
}
