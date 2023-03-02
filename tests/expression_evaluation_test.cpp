#include "gtest/gtest.h"
#include "iaq/solve/expression_evaluation.hpp"


TEST(test_expression_evaluation, t1)
{
    iaq::solve::ExpressionEvaluation exp_eval;
    ASSERT_DOUBLE_EQ(exp_eval.compute("33*3 + sin(90)"), 100);
    ASSERT_NEAR(exp_eval.compute("100 + 2 * (25*4+cos(90))"), 300, 3);
    ASSERT_EQ(exp_eval.compute("12+ 2*3-6/2+sqrt(3*3)"), 18);
    ASSERT_EQ(exp_eval.compute("9+(3-1)*3+8/2"), 19);
    ASSERT_EQ(exp_eval.compute("5+6*2"), 17);
}
