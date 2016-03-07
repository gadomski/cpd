#include "test/support.hpp"
#include "cpd/normalization.hpp"

namespace cpd {

class NormalizationTest : public FishTest {};

TEST_F(NormalizationTest, SourceTargetRows) {
    Normalization normalization(m_fish1, m_fish2, 1.0);
    EXPECT_EQ(m_fish1.rows(), normalization.source().rows());
    EXPECT_EQ(m_fish2.rows(), normalization.target().rows());
    EXPECT_GT(1.0, normalization.sigma2());
}
}
