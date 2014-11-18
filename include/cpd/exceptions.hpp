#pragma once

#include <exception>


namespace cpd
{


class dimension_mismatch : public std::runtime_error
{
public:
    dimension_mismatch(const std::string& msg) 
        : std::runtime_error(msg)
    {}
};


}
