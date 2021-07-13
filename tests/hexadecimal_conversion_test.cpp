#include "gtest/gtest.h"
#include "iaq/solve/hexadecimal_conversion.hpp"



TEST(HexConvTest, t1)
{
    const char* i = "中文";
    char o[15]={0};
    iaq::solve::HexConv()((unsigned char*)i, 6, o);
    fprintf(stderr, "%s\n", o);
}
