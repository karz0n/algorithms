#include "ArithmeticEvaluator.hpp"

#include <sstream>
#include <stdexcept>

#include "LinkedStack.hpp"

namespace {

enum class Operators {
    add,
    sub,
    mul,
    div
};

double calculate(double operands1, double operands2, Operators oper)
{
    double r = 0.0;
    switch (oper) {
    case Operators::add:
        r = operands2 + operands1;
        break;
    case Operators::sub:
        r = operands2 - operands1;
        break;
    case Operators::mul:
        r = operands2 * operands1;
        break;
    case Operators::div:
        r = operands2 / operands1;
        break;
    default:
        throw std::runtime_error("Unknown operator");
    }
    return r;
}

} // namespace

namespace algorithms {

double ArithmeticEvaluator::evaluate(const std::string& expression)
{
    LinkedStack<double> operands;
    LinkedStack<Operators> operators;

    double operands1 = 0.0;
    double operands2 = 0.0;
    double res = 0.0;
    Operators oper;

    std::istringstream iss(expression);
    while (iss) {
        auto c = iss.peek();
        if (iss.eof() || iss.bad()) {
            break;
        }

        switch (c) {
        case '(':
            iss.ignore();
            break;
        case ')':
            operands1 = operands.pop();
            operands2 = operands.pop();
            oper = operators.pop();
            res = calculate(operands1, operands2, oper);
            operands.push(res);
            iss.ignore();
            break;
        case '+':
            operators.push(Operators::add);
            iss.ignore();
            break;
        case '-':
            operators.push(Operators::sub);
            iss.ignore();
            break;
        case '*':
            operators.push(Operators::mul);
            iss.ignore();
            break;
        case '/':
            operators.push(Operators::div);
            iss.ignore();
            break;
        case ' ':
            iss.ignore();
            break;
        default:
            double o = 0.0;
            iss >> o;
            operands.push(o);
        }
    }

    return operands.pop();
}

} // namespace algorithms
