#include "gtest/gtest.h"
#include "iaq/solve/check_code.hpp"
#include <stdexcept>

TEST(test_check_code, positive)
{
    iaq::solve::CheckCode check_code;
    char final_data[11] = {0};
    check_code(iaq::solve::CheckCode::Method::kHamming, "101011", final_data);
    ASSERT_STREQ(final_data, "0111010011");
}

TEST(test_check_code, negative)
{
    ASSERT_TRUE(true);
}
