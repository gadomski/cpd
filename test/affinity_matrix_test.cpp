#include <gtest/gtest.h>
#include <cpd/affinity_matrix.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class AffinityMatrix : public RegistrationTest
{};


TEST_F(AffinityMatrix, MatchesReferenceImpl)
{
    arma::mat G;
    cpd::construct_affinity_matrix(m_Y, m_Y, 2, G);

    EXPECT_NEAR(1.0000, G(0), 0.0001);
    EXPECT_NEAR(0.0439, G(35, 0), 0.0001);
    EXPECT_NEAR(0.8825, G(3, 6), 0.0001);
    EXPECT_NEAR(1.0000, G(35, 35), 0.0001);
}


}
}
