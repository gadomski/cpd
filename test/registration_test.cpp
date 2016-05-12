#include "test/support.hpp"
#include "utils.hpp"

namespace cpd {

class RegistrationTest : public FishTest {};

TEST_F(RegistrationTest, DefaultSigma2) {
    double sigma2 = default_sigma2(m_fish1, m_fish2);
    EXPECT_NEAR(3.5, sigma2, 1e-8);
}
}
