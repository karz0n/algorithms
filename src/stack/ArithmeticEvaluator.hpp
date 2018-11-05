#ifndef ARITHMETICEVALUATOR_HPP
#define ARITHMETICEVALUATOR_HPP

#include <string>

namespace algorithms {

/**
 * Arithmetic evaluator which uses two stack to calculate any expression.
 */
class ArithmeticEvaluator {
public:
    static double evaluate(const std::string& expression);
};

} // namespace algorithms

#endif // ARITHMETICEVALUATOR_HPP
