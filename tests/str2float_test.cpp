#include "gtest/gtest.h"
#include "iaq/iaq.hpp"

using namespace iaq;

TEST(str2float, border_check)
{
    ASSERT_EQ(0, solve::StrToFloat()(NULL));
}


TEST(str2float, normal_input)
{
    ASSERT_EQ(1234, solve::StrToFloat()("1234"));
    ASSERT_EQ(-1234, solve::StrToFloat()("-1234"));
    ASSERT_EQ(12.34, solve::StrToFloat()("12.34", 2));
    ASSERT_EQ(0.123, solve::StrToFloat()("0.1234", 3));
}

TEST(str2float, inormal_input)
{
    ASSERT_EQ(0, solve::StrToFloat()("-fds2"));
    ASSERT_EQ(0, solve::StrToFloat()("3234fds2"));
    ASSERT_EQ(0, solve::StrToFloat()("fjdks3290"));
    ASSERT_EQ(0.123, solve::StrToFloat()("000.1234", 3));
    ASSERT_EQ(12.34, solve::StrToFloat()("012.34", 2));
}

