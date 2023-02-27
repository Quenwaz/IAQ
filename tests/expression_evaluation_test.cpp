#include "gtest/gtest.h"
#include "iaq/solve/expression_evaluation.hpp"


TEST(test_expression_evaluation, t1)
{
    const char* maze[] = {
        "111101011",
        "111100100",
        "111111101",
        "111101011",
        "111111111",
        "111111011",
        "110111111",
        "110111111",
        "011111111"
    };
    
    ASSERT_EQ(iaq::solve::ExpressionEvaluation().compute("(25+63)*2/67-19"), 17);
}
