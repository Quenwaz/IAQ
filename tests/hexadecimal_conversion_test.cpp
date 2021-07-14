#include "gtest/gtest.h"
#include "iaq/solve/hexadecimal_conversion.hpp"



TEST(HexConvTest, t1)
{
    const char* i = "中文";
    char o[13]={0};
    iaq::solve::HexConv()((unsigned char*)i, 6, o, false);
    ASSERT_STREQ(o, "e4b8ade69687");

    iaq::solve::HexConv()((unsigned char*)i, 6, o);
    ASSERT_STREQ(o, "E4B8ADE69687");

    char o2[7]={0};
    iaq::solve::HexConv()(o, 12, (unsigned char*)o2);

    ASSERT_STREQ(o2, i);
}
