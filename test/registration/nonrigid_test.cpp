#include <gtest/gtest.h>
#include <cpd/registration/nonrigid.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class NonrigidRegistration : public RegistrationTest
{};


TEST_F(NonrigidRegistration, InitializesWithDefaults)
{
    cpd::registration::Nonrigid reg;
}


TEST_F(NonrigidRegistration, RegistersData)
{
    cpd::registration::Nonrigid reg;
    cpd::registration::SpResult result = reg(m_X, m_Y);
    expect_matrices_near(m_X, result->Y, 0.0001);
}


}
}
