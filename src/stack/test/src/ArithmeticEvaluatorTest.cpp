#include <gtest/gtest.h>

#include "ArithmeticEvaluator.hpp"

using namespace algorithms;

TEST(ArithmeticEvaluation, Evaluate1)
{
    ASSERT_EQ(ArithmeticEvaluator::evaluate("((2 + 4) - 1 )"), 5);
}

TEST(ArithmeticEvaluation, Evaluate2)
{
    ASSERT_EQ(ArithmeticEvaluator::evaluate("((4 + 4) / 2 )"), 4);
}

TEST(ArithmeticEvaluation, Evaluate3)
{
    ASSERT_EQ(ArithmeticEvaluator::evaluate("(((2 * 2) + 1) * ((2 + 3) - 1))"), 20);
}
