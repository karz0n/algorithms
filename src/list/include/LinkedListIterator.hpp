#pragma once

#include <iterator>

#include "Node.hpp"

namespace algorithms {

/**
 * Simple linked list iterator.
 */
template<typename T>
class LinkedListIterator {
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;

public:
    LinkedListIterator()
        : _p{nullptr}
    {
    }

    explicit LinkedListIterator(Node<T>* front)
        : _p{front}
    {
    }

    LinkedListIterator<T>&
    operator=(const LinkedListIterator<T>& other)
    {
        if (this != &other) {
            _p = other._p;
        }
        return *this;
    }

    LinkedListIterator<T>&
    operator=(LinkedListIterator<T>&& other) noexcept
    {
        if (this != &other) {
            _p = other._p;
            other._p = nullptr;
        }
        return *this;
    }

    bool
    operator==(const LinkedListIterator<T>& other)
    {
        if (this != &other) {
            return (_p == other._p);
        }
        return true;
    }

    bool
    operator!=(const LinkedListIterator<T>& other)
    {
        return (*this != other);
    }

    T
    operator--(int)
    {
        T item = _p->item;
        _p = _p->prev;
        return item;
    }

    LinkedListIterator&
    operator--()
    {
        _p = _p->prev;
        return *this;
    }

    T
    operator++(int)
    {
        T item = _p->item;
        _p = _p->next;
        return item;
    }

    LinkedListIterator<T>&
    operator++()
    {
        _p = _p->next;
        return *this;
    }

    T&
    operator*()
    {
        return _p->item;
    }

    const T&
    operator*() const
    {
        return _p->item;
    }

private:
    Node<T>* _p;
};

} // namespace algorithms
