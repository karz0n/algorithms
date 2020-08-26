#pragma once

#include <string>

namespace algorithms {

/**
 * Arithmetic evaluator which uses two stack to calculate expression.
 */
class ArithmeticEvaluator {
public:
    static double
    evaluate(const std::string& expression);
};

} // namespace algorithms
