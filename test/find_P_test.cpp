#include <gtest/gtest.h>
#include <cpd/find_P.hpp>


namespace cpd
{
namespace test
{


TEST(FindP, MatchesReferenceImplWithoutFGT)
{
    arma::mat33 X, Y, PX;
    arma::vec3 P1, Pt1;
    X << 1 << 2 << 3 << arma::endr
      << 4 << 5 << 6 << arma::endr
      << 7 << 8 << 9 << arma::endr;
    Y << 10 << 11 << 12 << arma::endr
      << 13 << 14 << 15 << arma::endr
      << 16 << 17 << 18 << arma::endr;
    double L = cpd::find_P(X, Y, 93, 0.1, P1, Pt1, PX, false);

    EXPECT_NEAR(0.0011, P1(0), 0.0001);
    EXPECT_NEAR(0.0006, P1(1), 0.0001);
    EXPECT_NEAR(0.0003, P1(2), 0.0001);

    EXPECT_NEAR(0.0003, Pt1(0), 0.0001);
    EXPECT_NEAR(0.0006, Pt1(1), 0.0001);
    EXPECT_NEAR(0.0011, Pt1(2), 0.0001);

    EXPECT_NEAR(0.0055, PX(0), 0.0001);
    EXPECT_NEAR(0.0032, PX(1), 0.0001);
    EXPECT_NEAR(0.0015, PX(2), 0.0001);
    EXPECT_NEAR(0.0065, PX(3), 0.0001);
    EXPECT_NEAR(0.0038, PX(4), 0.0001);
    EXPECT_NEAR(0.0017, PX(5), 0.0001);
    EXPECT_NEAR(0.0076, PX(6), 0.0001);
    EXPECT_NEAR(0.0044, PX(7), 0.0001);
    EXPECT_NEAR(0.0020, PX(8), 0.0001);

    EXPECT_NEAR(-1.6807, L, 0.0001);
}


}
}
