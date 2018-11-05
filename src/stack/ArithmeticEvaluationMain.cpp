#include <gtest/gtest.h>

#include "ArithmeticEvaluator.hpp"

using namespace algorithms;

TEST(ArithmeticEvaluation, Main)
{
    ASSERT_TRUE(ArithmeticEvaluator::evaluate("((2 + 4) - 1 )") == 5);

    ASSERT_TRUE(ArithmeticEvaluator::evaluate("((4 + 4) / 2 )") == 4);

    ASSERT_TRUE(ArithmeticEvaluator::evaluate("(((2 * 2) + 1) * ((2 + 3) - 1))") == 20);
}
