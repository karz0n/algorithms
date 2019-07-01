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
template <typename T, typename Comparator>
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
        std::swap(_data[1], _data[_n--]);
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
        while (k > 1 && cmp(_data[k / 2].value(), _data[k].value())) {
            std::swap(_data[k / 2], _data[k]);
            k /= 2;
        }
    }

    void sink(std::size_t k, Comparator cmp = {})
    {
        while (2 * k <= _n) {
            std::size_t j = 2 * k;
            if (j < _n && cmp(_data[j].value(), _data[j + 1].value())) {
                j++;
            }
            if (!cmp(_data[k].value(), _data[j].value())) {
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
template <typename T, typename C = std::greater<std::optional<T>>>
using MinPriorityQueue = PriorityQueue<T, C>;

/**
 * Max priority queue class alias
 */
template <typename T, typename C = std::less<std::optional<T>>>
using MaxPriorityQueue = PriorityQueue<T, C>;

} // namespace algorithms

#endif // PRIORITYQUEUE_HPP
