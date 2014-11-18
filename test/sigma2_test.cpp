#include <gtest/gtest.h>
#include <cpd/sigma2.hpp>


namespace cpd
{
namespace test
{


TEST(Sigma2, MatchesReferenceImpl)
{
    arma::mat33 X, Y;
    X << 1 << 2 << 3 << arma::endr
      << 4 << 5 << 6 << arma::endr
      << 7 << 8 << 9 << arma::endr;
    Y << 10 << 11 << 12 << arma::endr
      << 13 << 14 << 15 << arma::endr
      << 16 << 17 << 18 << arma::endr;
    EXPECT_DOUBLE_EQ(93, get_sigma2(X, Y));
}


}
}
