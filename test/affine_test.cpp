#include "test/support.hpp"
#include "cpd/affine.hpp"

namespace cpd {

class AffineTest : public FishTest {};

TEST_F(AffineTest, StandaloneFunction) {
    auto result = affine(m_fish1, m_fish2);
    ASSERT_EQ(m_fish2.rows(), result.points.rows());
    EXPECT_TRUE(m_fish1.isApprox(result.points, 1e-4));
    EXPECT_TRUE(m_rotation.matrix().isApprox(result.rotation, 1e-4));
}
}
