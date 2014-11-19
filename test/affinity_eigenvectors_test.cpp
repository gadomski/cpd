#include <gtest/gtest.h>
#include <cpd/affinity_eigenvectors.hpp>

#include "fixtures.hpp"


namespace cpd
{
namespace test
{


class AffinityEigenvectors : public RegistrationTest
{};


TEST_F(AffinityEigenvectors, MatchesReferenceImpl)
{
    arma::mat Q, S;
    cpd::find_affinity_eigenvectors(m_Y, 2, 10, Q, S);

    EXPECT_NEAR(0.1651, Q(0), 0.0001);
    EXPECT_NEAR(-0.1978, Q(35, 9), 0.0001);
    EXPECT_NEAR(16.5205, S(0, 0), 0.01);
    EXPECT_NEAR(0.3057, S(9, 9), 0.01);
}


}
}
