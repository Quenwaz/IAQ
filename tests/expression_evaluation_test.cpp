#include "gtest/gtest.h"
#include "iaq/solve/expression_evaluation.hpp"
#include <stdexcept>

TEST(test_expression_evaluation, positive)
{
    iaq::solve::ExpressionEvaluation exp_eval;
    ASSERT_DOUBLE_EQ(exp_eval(".5*4"), 2);
    ASSERT_DOUBLE_EQ(exp_eval("5.*4"), 20);
    ASSERT_DOUBLE_EQ(exp_eval("2.5*4"), 10);
    ASSERT_DOUBLE_EQ(exp_eval("33*3 + sin(90)"), 100);
    ASSERT_NEAR(exp_eval("100 + 2 * (25*4+cos(90))"), 300, 3);
    ASSERT_EQ(exp_eval("12+ 2*3-6/2+sqrt(3^2)"), 18);
    ASSERT_EQ(exp_eval("9+(3-1)*3+8/2"), 19);
    ASSERT_EQ(exp_eval("5+6*2"), 17);
    ASSERT_EQ(exp_eval("myfunction(1,2,3)"), 6);
}

TEST(test_expression_evaluation, negative)
{
    iaq::solve::ExpressionEvaluation exp_eval;

    EXPECT_THROW(exp_eval("33*3 + sin90)"), std::logic_error);
    EXPECT_THROW(exp_eval("33*3 + sin(90"), std::logic_error);
    EXPECT_THROW(exp_eval("fjdskfjaldfjl"), std::logic_error);
    EXPECT_THROW(exp_eval("12343414321"), std::logic_error);
    EXPECT_THROW(exp_eval("12343#414$32%1"), std::logic_error);
}
