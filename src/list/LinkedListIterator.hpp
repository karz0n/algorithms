#ifndef LINKEDLISTITERATOR_HPP
#define LINKEDLISTITERATOR_HPP

#include <iterator>

#include "Node.hpp"

namespace algorithms {

/**
 *
 *  BidirectionalIterator = ForwardIterator + decrementable
 *  ForwardIterator = InputIterator + DefaultConstructible
 *  InputIterator = Iterator + EqualityComparable
 *  Iterator = CopyConstructible + CopyAssignable + Destructible
 *  CopyConstructible = MoveAssignable + appropriate operator overload
 *  MoveAssignable = appropriate operator overload
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
    /**
     * DefaultConstructible
     */
    LinkedListIterator()
        : _p{nullptr}
    { }

    /**
     * Destructible
     */
    ~LinkedListIterator() noexcept
    { }

    /**
     *
     */
    explicit LinkedListIterator(Node<T>* front)
        : _p{front}
    { }

    /**
     * CopyAssignable
     */
    LinkedListIterator<T>& operator=(const LinkedListIterator<T>& other)
    {
        if (this != &other) {
            _p = other._p;
        }
        return *this;
    }

    /**
     * MoveAssignable
     */
    LinkedListIterator<T>& operator=(LinkedListIterator<T>&& other)
    {
        if (this != &other) {
            _p = other._p;
            other._p = nullptr;
        }
        return *this;
    }

    /**
     * EqualityComparable
     */
    bool operator==(const LinkedListIterator<T>& other)
    {
        if (this != &other)
        {
            return (_p == other._p);
        }
        return true;
    }

    /**
     * InputIterator
     */
    bool operator!=(const LinkedListIterator<T>& other)
    {
        return !(*this == other);
    }

    /**
     * BidirectionalIterator
     */
    T operator--(int)
    {
        T item = _p->item;
        _p = _p->prev;
        return item;
    }

    /**
     * BidirectionalIterator
     */
    LinkedListIterator& operator--()
    {
        _p = _p->prev;
        return *this;
    }

    /**
     * InputIterator
     */
    T operator++(int)
    {
        T item = _p->item;
        _p = _p->next;
        return item;
    }

    /**
     * Iterator
     */
    LinkedListIterator<T>& operator++()
    {
        _p = _p->next;
        return *this;
    }

    /**
     * Iterator
     */
    T& operator*()
    {
        return _p->item;
    }

    /**
     * Iterator
     */
    const T& operator*() const
    {
        return _p->item;
    }

private:
    Node<T>* _p;
};

} // namespace name

#endif // LINKEDLISTITERATOR_HPP
