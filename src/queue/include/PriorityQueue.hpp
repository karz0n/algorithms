#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <functional>
#include <vector>
#include <optional>

#include "Queue.hpp"

namespace algorithms {

/**
 * Priority queue class implementation based on binary tree and binary heap ordering.
 *
 * Properties:
 *  - parent node of k is k/2
 *  - children of node at k are at 2k and 2k+1
 *
 * Invariants:
 *  - largest key is a[1] which is root of binary tree
 *
 */
template<typename T, typename Less = std::less<std::optional<T>>>
class PriorityQueue : public Queue<T> {
public:
    using Value = std::optional<T>;

    PriorityQueue(std::size_t capacity)
        : _size{1}
    {
        _data.resize(capacity + 1);
    }

    void enqueue(const T& value) override
    {
#ifndef NDEBUG
        if (_data.size() == _size) {
            throw std::overflow_error("Queue is full");
        }
#endif
        _data[++_size] = std::make_optional<T>(value);
        swim(_size);
    }

    T dequeue() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
#endif
        auto value = _data[1].value();
        std::swap(_data[_size--], _data[1]);
        sink(1);
        _data[_size + 1] = std::optional<T>{};
        return value;
    }

    bool isEmpty() const override
    {
        return (_size == 1);
    }

private:

    void swim(std::size_t k, Less less = {})
    {
        while (k > 1 && less(_data[k / 2], _data[k])) {
            std::swap(_data[k], _data[k / 2]);
            k /= 2;
        }
    }

    void sink(std::size_t k, Less less = {})
    {
        while (2 * k <= _size) {
            std::size_t j = 2 * k;
            if (j < _size && less(_data[j], _data[j + 1])) {
                 j++;
            }
            if (!less(_data[k], _data[j])) {
                 break;
            }
            std::swap(_data[k], _data[j]);
            k = j;
        }
    }

private:
    std::size_t _size;
    std::vector<Value> _data;
};

} // namespace algorithms

#endif // PRIORITYQUEUE_HPP
