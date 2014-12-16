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

#include <chrono>
#include <ctime>
#include <ostream>


namespace cpd
{
namespace test
{


class Timer
{
public:

    void start();
    void end();

    inline float clock_time() const
    {
        return 1000.0 * (m_c_end - m_c_start) / CLOCKS_PER_SEC;
    }
    inline float chrono_time() const
    {
        return std::chrono::duration<double, std::milli>(m_t_end - m_t_start).count();
    }

private:
    std::clock_t m_c_start, m_c_end;
    std::chrono::high_resolution_clock::time_point m_t_start, m_t_end;

};


std::ostream& operator<<(std::ostream& os, const Timer& timer);


}
}


