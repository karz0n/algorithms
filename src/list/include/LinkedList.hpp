#pragma once

#include <stdexcept>

#include "List.hpp"
#include "Node.hpp"
#include "LinkedListIterator.hpp"

namespace algorithms {

template<typename T>
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

    ~LinkedList() override
    {
        while (_front) {
            auto* n = _front->next;
            delete _front;
            _front = n;
        }
    }

    LinkedListIterator<T>
    begin() const
    {
        return Iterator{_front};
    }

    LinkedListIterator<T>
    end() const
    {
        return Iterator{};
    }

    T&
    front() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"Queue is empty"};
        }
#endif
        return _front->item;
    }

    const T&
    front() const override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"List is empty"};
        }
#endif
        return _front->item;
    }

    T&
    back() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"List is empty"};
        }
#endif
        return _back->item;
    }

    const T&
    back() const override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"List is empty"};
        }
#endif
        return _back->item;
    }

    void
    pushFront(const T& item) override
    {
        auto* n = new NodeType{item};
        n->next = _front;
        if (_front) {
            _front->prev = n;
        }
        else {
            _back = n;
        }
        _front = n;
    }

    T
    popFront() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"List is empty"};
        }
#endif
        T item = _front->item;

        auto* n = _front;
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

    void
    pushBack(const T& item) override
    {
        auto* n = new NodeType{item};
        n->prev = _back;
        if (_back) {
            _back->next = n;
        }
        else {
            _front = n;
        }
        _back = n;
    }

    T
    popBack() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error{"List is empty"};
        }
#endif
        T item = _back->item;

        auto* n = _back;
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

    [[nodiscard]] bool
    empty() const override
    {
        return (_front == nullptr);
    }

private:
    NodeType* _front;
    NodeType* _back;
};

} // namespace algorithms
