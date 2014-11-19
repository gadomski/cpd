#include <gtest/gtest.h>
#include <cpd/registration/nonrigid_lowrank.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class NonrigidLowrankRegistration : public RegistrationTest
{};


TEST_F(NonrigidLowrankRegistration, InitializesWithDefaults)
{
    cpd::registration::NonrigidLowrank reg;
}


TEST_F(NonrigidLowrankRegistration, RegistersData)
{
    cpd::registration::NonrigidLowrank reg;
    cpd::registration::SpResult result = reg(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.1);
}


}
}
