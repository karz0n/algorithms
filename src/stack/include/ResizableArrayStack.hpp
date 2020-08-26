#pragma once

#include <algorithm>
#include <stdexcept>

#include "Stack.hpp"

namespace algorithms {

/**
 * Resizable stack implementation.
 */
template<typename T>
class ResizableArrayStack : public Stack<T> {
public:
    explicit ResizableArrayStack(std::size_t size = 1)
        : _dpos{0}
        , _size{size}
        , _data{nullptr}
    {
#ifndef NDEBUG
        if (size == 0) {
            throw std::invalid_argument{"Capacity is invalid"};
        }
#endif
        _data = new T[_size = size];
    }

    ~ResizableArrayStack() override
    {
        if (_data) {
            delete[] _data;
        }
    }

    void
    push(const T& item) override
    {
        if (_dpos == _size) {
            resize(_size * 2);
        }
        _data[_dpos++] = item;
    }

    T
    pop() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::underflow_error{"Stack is empty"};
        }
#endif
        if (_dpos == _size / 4) {
            resize(_size / 2);
        }
        return _data[--_dpos];
    }

    [[nodiscard]] bool
    empty() const override
    {
        return (_dpos == 0);
    }

private:
    void
    resize(std::size_t size)
    {
        T* data = new T[size];
        std::move(_data, _data + _dpos, data);
        delete[] _data;
        _data = data;
        _size = size;
    }

private:
    std::size_t _dpos;
    std::size_t _size;
    T* _data;
};

} // namespace algorithms
