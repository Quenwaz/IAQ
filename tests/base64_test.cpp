#include "gtest/gtest.h"
#include "iaq/solve/base64.hpp"



TEST(Base64Test, encode)
{
    const char* i = "中文";
    char o[9]={0};
    iaq::solve::base64::Encode()((unsigned char*)i, 6, o);
    ASSERT_EQ(8, iaq::solve::base64::Encode()((unsigned char*)i, 6, nullptr));
    ASSERT_STREQ(o, "5Lit5paH");

    const char* i1 = "binary\x00string";
    char o1[21]={0};
    iaq::solve::base64::Encode()((unsigned char*)i1, 13, o1);
    ASSERT_EQ(20, iaq::solve::base64::Encode()((unsigned char*)i1, 13, nullptr));
    ASSERT_STREQ(o1, "YmluYXJ5AHN0cmluZw==");

    const char* i2 = "quenwaz";
    char o2[13]={0};
    iaq::solve::base64::Encode()((unsigned char*)i2, 7, o2);
    ASSERT_EQ(12, iaq::solve::base64::Encode()((unsigned char*)i2, 7, nullptr));
    ASSERT_STREQ(o2, "cXVlbndheg==");

    const char* i5 = "感谢七月让我遇见了你+///++++";
    char o5[53]={0};
    iaq::solve::base64::Encode()((unsigned char*)i5, 38, o5);
    ASSERT_EQ(52, iaq::solve::base64::Encode()((unsigned char*)i5, 38, nullptr));
    ASSERT_STREQ(o5, "5oSf6LCi5LiD5pyI6K6p5oiR6YGH6KeB5LqG5L2gKy8vLysrKys=");

    // safe mode
    const char* i3 = "quenwaz";
    char o3[11]={0};
    iaq::solve::base64::Encode()((unsigned char*)i3, 7, o3, true);
    ASSERT_EQ(10, iaq::solve::base64::Encode()((unsigned char*)i3, 7, nullptr, true));
    ASSERT_STREQ(o3, "cXVlbndheg");

    const char* i4 = "i\xb7\x1d\xfb\xef\xff";
    char o4[9]={0};
    iaq::solve::base64::Encode()((unsigned char*)i4, 6, o4, true);
    ASSERT_EQ(8, iaq::solve::base64::Encode()((unsigned char*)i4, 6, nullptr));
    ASSERT_STREQ(o4, "abcd--__");
}


TEST(Base64Test, decode)
{
    const char* i = "5Lit5paH";
    unsigned char o[7]={0};
    iaq::solve::base64::Decode()(i, 8, o);
    ASSERT_EQ(6, iaq::solve::base64::Decode()(i, 8, nullptr));
    ASSERT_STREQ((const char*)o, "中文");

    const char* i1 = "cXVlbndheg==";
    unsigned char o1[8]={0};
    iaq::solve::base64::Decode()(i1, 12, o1);
    ASSERT_EQ(7, iaq::solve::base64::Decode()(i1, 12, nullptr));
    ASSERT_STREQ((const char*)o1, "quenwaz");

    // safe mode
    const char* i2 = "cXVlbndheg";
    unsigned char o2[8]={0};
    iaq::solve::base64::Decode()(i2, 10, o2);
    ASSERT_EQ(7, iaq::solve::base64::Decode()(i2, 10, nullptr));
    ASSERT_STREQ((const char*)o2, "quenwaz");
}