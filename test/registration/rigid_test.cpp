#include <gtest/gtest.h>
#include <cpd/registration/rigid.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class RigidRegistration : public RegistrationTest
{};


TEST_F(RigidRegistration, InitializesWithDefaults)
{
    cpd::registration::Rigid reg;
}


TEST_F(RigidRegistration, RegistersData)
{
    cpd::registration::Rigid reg;
    cpd::registration::SpResult result = reg(m_X, m_Y);
    expect_matrices_near(m_X, m_Y, 0.001);
}


}
}
