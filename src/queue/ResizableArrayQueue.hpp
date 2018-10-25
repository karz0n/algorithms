#ifndef RESIZABLEARRAYQUEUE_HPP
#define RESIZABLEARRAYQUEUE_HPP

#include <stdexcept>

#include "Queue.hpp"

namespace algorithms {

template <typename T>
class ResizableArrayQueue : public Queue<T> {
public:
    ResizableArrayQueue(std::size_t size = 1)
        : _size{0}
        , _epos{0}
        , _dpos{0}
        , _data{nullptr}
    {
#ifndef NDEBUG
        if (size == 0) {
            throw std::invalid_argument("Capacity is invalid");
        }
#endif
        _data = new T[_size = size];
    }

    ~ResizableArrayQueue() override
    {
        if (_data) {
            delete[] _data;
        }
    }

    void enqueue(const T& item) override
    {
        if (_epos == _size) {
            resize(_size * 2);
        }
        _data[_epos++] = item;
    }

    T dequeue() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
#endif
        if (_epos - _dpos == _size / 4)
        {
            resize(_size / 2);
        }

        T item = _data[_dpos++];
        if (_dpos == _epos) {
            _dpos = 0;
            _epos = 0;
        }
        return item;
    }

    bool isEmpty() const override
    {
        return (_epos == _dpos);
    }

private:
    void resize(std::size_t size)
    {
        T* data = new T[size];
        std::move(_data + _dpos, _data + _epos, data);
        delete[] _data;
        _epos = _epos - _dpos;
        _dpos = 0;
        _data = data;
        _size = size;
    }

private:
    std::size_t _epos;
    std::size_t _dpos;
    std::size_t _size;
    T* _data;
};

} // namespace algorithms

#endif // RESIZABLEARRAYQUEUE_HPP
