#include "test/support.hpp"
#include "cpd/nonrigid.hpp"

namespace cpd {

class NonrigidTest : public FishTest {};

TEST_F(NonrigidTest, StandaloneFunction) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    auto actual = nonrigid(m_fish1, m_fish2);
    ASSERT_EQ(expected.rows(), actual.points.rows());
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}

TEST_F(NonrigidTest, ClassBased) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    Nonrigid nonrigid;
    auto actual = nonrigid.compute(m_fish1, m_fish2);
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}

TEST_F(NonrigidTest, WithSigma2) {
    auto expected = load_test_data_matrix("fish-nonrigid-3-3.txt");
    auto actual = nonrigid(m_fish1, m_fish2, 1.0);
    EXPECT_TRUE(expected.isApprox(actual.points, 0.5));
}
}
