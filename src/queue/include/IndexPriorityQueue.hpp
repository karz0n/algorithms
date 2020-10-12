#pragma once

#include <vector>
#include <stdexcept>

namespace algorithms {

/**
 * Class represents a fixed indexed priority queue of generic keys.
 */
template<typename T, typename Comparator>
class IndexPriorityQueue {
public:
    explicit IndexPriorityQueue(std::size_t capacity)
        : _pq(capacity + 1, -1)
        , _qp(capacity + 1, -1)
        , _keys(capacity + 1)
        , _size{0}
    {
#ifndef NDEBUG
        if (capacity == 0) {
            throw std::invalid_argument{"Invalid capacity value"};
        }
#endif
    }

    void
    push(std::size_t index, const T& value)
    {
#ifndef NDEBUG
        if (index >= _keys.size()) {
            throw std::invalid_argument{"Invalid index value"};
        }
        if (contains(index)) {
            throw std::logic_error{"Index is already occupied"};
        }
#endif
        _size++;
        _qp[index] = _size;
        _pq[_size] = index;
        _keys[index] = value;
        swim(_size);
    }

    [[nodiscard]] std::size_t
    pop()
    {
#ifndef NDEBUG
        if (_size == 0) {
            throw std::logic_error{"Queue is empty"};
        }
#endif
        int min = _pq[1];
        exchange(1, _size--);
        sink(1);
        _qp[min] = -1;
        _pq[_size + 1] = -1;
        _keys[min] = T{};
        return min;
    }

    void
    decreaseKey(std::size_t index, const T& value)
    {
#ifndef NDEBUG
        if (index >= _keys.size()) {
            throw std::invalid_argument{"Invalid index value"};
        }
        if (!contains(index)) {
            throw std::logic_error{"Element is absent"};
        }
        if (compare(value, _keys[index])) {
            throw std::logic_error{"Element is invalid"};
        }
#endif
        _keys[index] = value;
        swim(_qp[index]);
    }

    [[nodiscard]] bool
    contains(std::size_t index) const
    {
#ifndef NDEBUG
        if (index >= _keys.size()) {
            throw std::invalid_argument{"Invalid index value"};
        }
#endif
        return _qp[index] != -1;
    }

    [[nodiscard]] std::size_t
    topIndex() const
    {
#ifndef NDEBUG
        if (_size == 0) {
            throw std::logic_error{"Queue is empty"};
        }
#endif
        return _pq[1];
    }

    [[nodiscard]] T
    topKey() const
    {
#ifndef NDEBUG
        if (_size == 0) {
            throw std::logic_error{"Queue is empty"};
        }
#endif
        return _keys[_pq[1]];
    }

    [[nodiscard]] bool
    empty() const
    {
        return (_size == 0);
    }

    [[nodiscard]] std::size_t
    size() const
    {
        return _size;
    }

private:
    void
    swim(std::size_t k)
    {
        while (k > 1 && compare(k / 2, k)) {
            exchange(k, k / 2);
            k /= 2;
        }
    }

    void
    sink(std::size_t k)
    {
        while (2 * k <= _size) {
            std::size_t j = 2 * k;
            if (j < _size && compare(j, j + 1)) {
                j++;
            }
            if (!compare(k, j)) {
                break;
            }
            exchange(k, j);
            k = j;
        }
    }

    void
    exchange(std::size_t i, std::size_t j)
    {
        // Swap indexes at i and j heap positions
        std::swap(_pq[i], _pq[j]);
        // Update heap positions for swapped indexes
        _qp[_pq[i]] = i;
        _qp[_pq[j]] = j;
    }

    bool
    compare(std::size_t i, std::size_t j)
    {
        return _comparator(_keys[_pq[i]], _keys[_pq[j]]);
    }

private:
    std::vector<int> _pq;
    std::vector<int> _qp;
    std::vector<T> _keys;
    std::size_t _size;
    Comparator _comparator;
};

/**
 * Index min priority queue class alias
 */
template<typename T, typename C = std::greater<T>>
using IndexMinPriorityQueue = IndexPriorityQueue<T, C>;

/**
 * Index max priority queue class alias
 */
template<typename T, typename C = std::less<T>>
using IndexMaxPriorityQueue = IndexPriorityQueue<T, C>;

} // namespace algorithms