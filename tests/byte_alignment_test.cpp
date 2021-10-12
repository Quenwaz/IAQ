#include "gtest/gtest.h"
#include "iaq/solve/byte_alignment.hpp"

#pragma pack(4)
struct Memory{
    char a;
    double b;
    short c;
}__attribute__((aligned(4)));
#pragma pack()

TEST(ByteAlignTest, t1)
{
    const auto s = sizeof(Memory);

    iaq::solve::bytealign::ByteAlign bytealign;
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS1), 8);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS2), 12);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS3), 16);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS4), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS5), 32);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS6), 32);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS7), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS8), 48);
}