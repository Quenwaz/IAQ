#include "gtest/gtest.h"
#include "iaq/solve/base64.hpp"



TEST(HexConvTest, t1)
{
    const char* i = "中文";
    char o[9]={0};
    iaq::solve::base64::Encode()((unsigned char*)i, 6, o);
    ASSERT_STREQ(o, "5Lit5paH");

    const char* i1 = "binary\x00string";
    char o1[21]={0};
    iaq::solve::base64::Encode()((unsigned char*)i1, 13, o1);
    ASSERT_STREQ(o1, "YmluYXJ5AHN0cmluZw==");

    const char* i2 = "quenwaz";
    char o2[13]={0};
    iaq::solve::base64::Encode()((unsigned char*)i2, 7, o2);
    ASSERT_STREQ(o2, "cXVlbndheg==");
}
