#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <stdexcept>

#include "List.hpp"
#include "Node.hpp"
#include "LinkedListIterator.hpp"

namespace algorithms {

template <typename T>
class LinkedList : public List<T> {
public:
    using NodeType = Node<T>;
    using Iterator = LinkedListIterator<T>;

public:
    LinkedList()
        : _front{nullptr}
        , _back{nullptr}
    {
    }

    LinkedListIterator<T> begin() const
    {
        return LinkedListIterator<T>(_front);
    }

    LinkedListIterator<T> end() const
    {
        return LinkedListIterator<T>();
    }

    T& front() override
    {
        return _front->item;
    }

    const T& front() const override
    {
        return _front->item;
    }

    T& back() override
    {
        return _back->item;
    }

    const T& back() const override
    {
        return _back->item;
    }

    void pushFront(const T& item) override
    {
        NodeType* n = new NodeType{item};
        n->next = _front;
        if (_front) {
            _front->prev = n;
        } else {
            _back = n;
        }
        _front = n;
    }

    T popFront() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
#endif
        T item = _front->item;

        NodeType* n = _front;
        _front = _front->next;
        delete n;

        if (_front) {
            _front->prev = nullptr;
        }
        else {
            _back = nullptr;
        }

        return item;
    }

    void pushBack(const T& item) override
    {
        NodeType* n = new NodeType{item};
        n->prev = _back;
        if (_back) {
            _back->next = n;
        } else {
            _front = n;
        }
        _back = n;
    }

    T popBack() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
#endif
        T item = _back->item;

        NodeType* n = _back;
        _back = _back->prev;
        delete n;

        if (_back) {
            _back->next = nullptr;
        }
        else {
            _front = nullptr;
        }

        return item;
    }

    bool isEmpty() const override
    {
        return (_front == nullptr);
    }

private:
    NodeType* _front;
    NodeType* _back;
};

} // namespace algorithms

#endif // LINKEDLIST_HPP
