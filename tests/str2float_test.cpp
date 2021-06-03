#include "gtest/gtest.h"
#include "iaq/str2float.hpp"


TEST(str2float, border_check)
{
    ASSERT_EQ(0, solve::str_to_float(NULL));
}


TEST(str2float, white_check)
{
    ASSERT_EQ(1234, solve::str_to_float("1234"));
    ASSERT_EQ(-1234, solve::str_to_float("-1234"));
    ASSERT_EQ(12.34, solve::str_to_float("12.34", 2));
    ASSERT_EQ(0.123, solve::str_to_float("0.1234", 3));
}

