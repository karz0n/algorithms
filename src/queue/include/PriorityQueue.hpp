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
template<typename T, typename Comparator>
class PriorityQueue : public Queue<T> {
public:
    using Value = std::optional<T>;

    PriorityQueue()
        : PriorityQueue{1}
    {
    }

    PriorityQueue(std::size_t capacity)
        : _n{0}
    {
        _data.resize(capacity + 1);
    }

    void enqueue(const T& value) override
    {
        /** Increase the size */
        if (_n == _data.size() - 1) {
            _data.resize(_data.size() * 2);
        }

        _data[++_n] = std::make_optional<T>(value);
        swim(_n);
    }

    T dequeue() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::underflow_error("Queue is empty");
        }
#endif
        auto value = _data[1].value();
        std::swap(_data[_n--], _data[1]);
        sink(1);
        _data[_n + 1].reset();

        /** Reduce the size */
        if (_n > 0 && _n == ((_data.size() - 1) / 4)) {
            _data.resize(_data.size() / 2);
            _data.shrink_to_fit();
        }

        return value;
    }

    bool empty() const override
    {
        return (_n == 0);
    }

private:

    void swim(std::size_t k, Comparator cmp = {})
    {
        while (k > 1 && cmp(_data[k / 2], _data[k])) {
            std::swap(_data[k], _data[k / 2]);
            k /= 2;
        }
    }

    void sink(std::size_t k, Comparator cmp = {})
    {
        while (2 * k <= _n) {
            std::size_t j = 2 * k;
            if (j < _n && cmp(_data[j], _data[j + 1])) {
                 j++;
            }
            if (!cmp(_data[k], _data[j])) {
                 break;
            }
            std::swap(_data[k], _data[j]);
            k = j;
        }
    }

private:
    std::size_t _n;
    std::vector<Value> _data;
};

/**
 * Min priority queue class alias
 */
template <typename T>
using MinPriorityQueue = PriorityQueue<T, std::less<std::optional<T>>>;

/**
 * Max priority queue class alias
 */
template <typename T>
using MaxPriorityQueue = PriorityQueue<T, std::greater<std::optional<T>>>;

} // namespace algorithms

#endif // PRIORITYQUEUE_HPP
