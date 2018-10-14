#ifndef RESIZABLESTACK_HPP
#define RESIZABLESTACK_HPP

#include <stdexcept>
#include <algorithm>

#include "Stack.hpp"

namespace algorithms {

template<typename T>
class ResizableStack : public Stack<T> {
public:
    ResizableStack(std::size_t size)
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

    void push(const T& item) override
    {
        if (_n == _s) {
            resize(_s * 2);
        }
        _data[_n++] = item;
    }

    T pop() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
#endif
        if (_n == _s / 4) {
            resize(_s / 2);
        }
        return _data[--_n];
    }

    bool isEmpty() const override
    {
        return (_n == 0);
    }

    void resize(std::size_t size)
    {
        T* data = new T[size];
        std::move(_data, _data + _n, data);
        delete[] _data;
        _data = data;
        _s = size;
    }

private:
    std::size_t _n;
    std::size_t _s;
    T* _data;
};

} // namespace algorithms

#endif // RESIZABLESTACK_HPP
