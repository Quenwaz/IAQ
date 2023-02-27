#include "gtest/gtest.h"
#define BYTE_ALIGN_8
#include "iaq/solve/byte_alignment.hpp"



TEST(ByteAlignTest, t1)
{
    iaq::solve::bytealign::ByteAlign bytealign;
#ifdef BYTE_ALIGN_2
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS1), 6);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS2), 8);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS3), 14);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS4), 22);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS5), 22);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS6), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS7), 16);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS8), 48);
#elif defined(BYTE_ALIGN_4)
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS1), 8);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS2), 12);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS3), 16);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS4), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS5), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS6), 28);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS7), 20);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS8), 48);
#elif defined(BYTE_ALIGN_8)
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS1), 8);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS2), 12);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS3), 16);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS4), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS5), 32);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS6), 32);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS7), 24);
    EXPECT_EQ(bytealign(iaq::solve::bytealign::kS8), 48);
#endif
}