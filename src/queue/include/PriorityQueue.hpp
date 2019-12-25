#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <functional>
#include <optional>

namespace algorithms {

/** Default capacity for the empty queue */
constexpr std::size_t DEFAULT_CAPACITY = 15;

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
class PriorityQueue {
public:
    using Value = std::optional<T>;

    PriorityQueue()
        : _size{0}
        , _capacity{0}
        , _data{nullptr}
    {
        resize(DEFAULT_CAPACITY);
    }

    ~PriorityQueue()
    {
        if (_data) {
            delete[] _data;
        }
    }

    void push(const T& value)
    {
        /** Increase the size */
        if (_size == _capacity - 1) {
            resize(_capacity * 2);
        }

        _data[++_size] = std::make_optional<T>(value);
        swim(_size);
    }

    T pop()
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        auto value = _data[1].value();
        std::swap(_data[1], _data[_size--]);
        sink(1);
        _data[_size + 1].reset();

        /** Reduce the size */
        if (_size > 0 && _size == ((_capacity - 1) / 4)) {
            resize(_capacity / 2);
        }

        return value;
    }

    const T& top() const
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _data[1].value();
    }

    const T& bottom() const
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _data[_size].value();
    }

    bool empty() const
    {
        return (_size == 0);
    }

    std::size_t size() const
    {
        return _size;
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
        while (2 * k <= _size) {
            std::size_t j = 2 * k;
            if (j < _size && cmp(_data[j].value(), _data[j + 1].value())) {
                j++;
            }
            if (!cmp(_data[k].value(), _data[j].value())) {
                break;
            }
            std::swap(_data[k], _data[j]);
            k = j;
        }
    }

    void resize(std::size_t capacity)
    {
        if (capacity == _capacity) {
            return;
        }

        Value* data = new Value[capacity];
        if (!empty()) {
            std::move(_data + 1, _data + _size + 1, data + 1);
        }

        _capacity = capacity;
        if (_data) {
            delete[] _data;
        }
        _data = data;
    }

private:
    std::size_t _size;
    std::size_t _capacity;
    Value* _data;
};

/**
 * Min priority queue class alias
 */
template<typename T, typename C = std::greater<T>>
using MinPriorityQueue = PriorityQueue<T, C>;

/**
 * Max priority queue class alias
 */
template<typename T, typename C = std::less<T>>
using MaxPriorityQueue = PriorityQueue<T, C>;

} // namespace algorithms

#endif // PRIORITYQUEUE_HPP
