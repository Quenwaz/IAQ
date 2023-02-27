#include "gtest/gtest.h"
#include "iaq/iaq.hpp"


TEST(large_number_calculation_test, t1)
{
    using iaq::solve::CalculateBigNumbers;
    char result[32]={0};
    int len = sizeof result;
    
    CalculateBigNumbers()(CalculateBigNumbers::kAdd, "1234567890134567832311233", "789315485321511313204313112", result, &len);
    ASSERT_STREQ(result, "790550053211645881036624345");
}