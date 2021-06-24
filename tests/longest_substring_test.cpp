#include "gtest/gtest.h"
#include "iaq/solve/longest_substring.hpp"


class LongSubStrNoRepeatTest : public::testing::TestWithParam<iaq::solve::LongSubStrNoRepeat>
{

};


TEST_P(LongSubStrNoRepeatTest, t1)
{
    iaq::solve::LongSubStrNoRepeat longest_substring = GetParam();
    
    ASSERT_EQ(longest_substring(""), 0);
    ASSERT_EQ(longest_substring(" "), 1);
    ASSERT_EQ(longest_substring("au"), 2);
    ASSERT_EQ(longest_substring("aab"), 2);
    ASSERT_EQ(longest_substring("dvdf"), 3);
    ASSERT_EQ(longest_substring("abba"), 2);
    ASSERT_EQ(longest_substring("abcabcbb"), 3);
    ASSERT_EQ(longest_substring("bbbbb"), 1);
    ASSERT_EQ(longest_substring("pwwkew"), 3);
}

INSTANTIATE_TEST_CASE_P(t1, LongSubStrNoRepeatTest, testing::Values(iaq::solve::LongSubStrNoRepeat(iaq::V1), iaq::solve::LongSubStrNoRepeat(iaq::V2)));