#include "gtest/gtest.h"
#include "iaq/solve/unicode.hpp"



TEST(UnicodeTest, encode)
{
    const wchar_t* i = L"中文abc";

    char o[30]={0};
    iaq::solve::unicode::Encode()(i, 5, o);
    ASSERT_STREQ(o, "\\u4e2d\\u6587abc");

    char o1[30]={0};
    iaq::solve::unicode::Encode()(i, 5, o1, false, false);
    ASSERT_STREQ(o1, "4e2d6587006100620063");

    iaq::solve::unicode::Encode()(i, 5, o1, true, false);
    ASSERT_STREQ(o1, "4E2D6587006100620063");
}


TEST(UnicodeTest, decode)
{
    
    const char* i = "\\u4e2d\\u6587abc";

    wchar_t o[6]={0};
    iaq::solve::unicode::Decode()(i, 15, o, true);
    ASSERT_STREQ(o, L"中文abc");

    const char* i1 = "4e2d6587006100620063";
    iaq::solve::unicode::Decode()(i1, 20, o, false);
    ASSERT_STREQ(o, L"中文abc");

    const char* i2 = "4E2D6587006100620063";
    iaq::solve::unicode::Decode()(i2, 20, o, false);
    ASSERT_STREQ(o, L"中文abc");
}