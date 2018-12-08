#ifndef FIXEDARRAYSTACK_HPP
#define FIXEDARRAYSTACK_HPP

#include <stdexcept>

#include "Stack.hpp"

namespace algorithms {

/**
 * Fixed size stack implementation.
 */
template<typename T>
class FixedArrayStack : public Stack<T> {
public:
    FixedArrayStack(std::size_t size)
        : _n{0}
        , _s{size}
    {
#ifndef NDEBUG
        if (size == 0) {
            throw std::invalid_argument("Capacity is invalid");
        }
#endif
        _data = new T[size];
    }

    ~FixedArrayStack() override
    {
        delete[] _data;
    }

    void push(const T& item) override
    {
#ifndef NDEBUG
        if (_n == _s) {
            throw std::overflow_error("Stack is overflow");
        }
#endif
        _data[_n++] = item;
    }

    T pop() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
#endif
        return _data[--_n];
    }

    bool isEmpty() const override
    {
        return (_n == 0);
    }

private:
    std::size_t _n;
    std::size_t _s;
    T* _data;
};

} // namespace algorithms

#endif // FIXEDARRAYSTACK_HPP
