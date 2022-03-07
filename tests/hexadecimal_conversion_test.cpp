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


    char o3[(sizeof(intptr_t) << 1) + 1]={0};
    iaq::solve::HexConv()(12345, o3);
    ASSERT_STREQ(o3, sizeof(intptr_t) ==8 ?"0000000000003039":"00003039");


    intptr_t data = 0;
    iaq::solve::HexConv()(o3, sizeof(intptr_t) << 1, data);
    ASSERT_EQ(data, 12345);

    char hexname[]="433a5c55736572735c5175656e77617a5c4465736b746f705ce585b8e59e8be8aebee8aea142e6a8a1e59d97efbc88e68e92e7aea12de6b599e6b19fefbc89e4bfaee8aea2202d20436f70792e647767";
    char name[81] = {0};
    iaq::solve::HexConv()(hexname, 160, (unsigned char*)name);

    int debug = 0;
}
