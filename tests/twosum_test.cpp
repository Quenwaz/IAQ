#include "gtest/gtest.h"
#include <vector>
#include "iaq/iaq.hpp"

using namespace iaq;

TEST(twosum, input)
{
    ASSERT_EQ(solve::TwoSum()(std::vector<int>(), 5), std::vector<int>());
}

TEST(twosum, t1)
{
    std::vector<int> input{1, 3, 2};
    std::vector<int> output{0, 2};
    solve::TwoSum two_sum(iaq::V1);
    EXPECT_EQ(output, two_sum(input, 3));
    two_sum.SetVersion(iaq::V2);
    EXPECT_EQ(output, two_sum(input, 3));
    two_sum.SetVersion(iaq::V3);
    ASSERT_EQ(output, two_sum(input, 3));
}

TEST(twosum, t2)
{
    std::vector<int> input{0,1,-1,5,2,8,3,4,9};
    const std::vector<int> output1{0, 6};

    solve::TwoSum two_sum(iaq::V1);
    EXPECT_EQ(output1, two_sum(input, 3));
    const std::vector<int> output2{1, 4};
    two_sum.SetVersion(iaq::V2);
    EXPECT_EQ(output2, two_sum(input,3));
    two_sum.SetVersion(iaq::V3);
    ASSERT_EQ(output2, two_sum(input,3));
}


TEST(twosum, t4)
{
    std::vector<int> input{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> output{1, 9};
    solve::TwoSum two_sum(iaq::V1);
    EXPECT_EQ(output, two_sum(input, 10));
    two_sum.SetVersion(iaq::V2);
    output={4, 6};
    EXPECT_EQ(output, two_sum(input, 10));
    two_sum.SetVersion(iaq::V3);
    ASSERT_EQ(output, two_sum(input, 10));
}


