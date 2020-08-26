#pragma once

#include <stdexcept>

#include "Stack.hpp"

namespace algorithms {

/**
 * Linked list stack implementation.
 */
template<typename T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack()
        : _first{nullptr}
    {
    }

    ~LinkedStack() override
    {
        while (_first) {
            auto* n = _first->next;
            delete _first;
            _first = n;
        }
    }

    void
    push(const T& item) override
    {
        _first = new Node{item, _first};
    }

    T
    pop() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::underflow_error{"Stack is empty"};
        }
#endif
        T item = _first->item;
        auto* n = _first->next;
        delete _first;
        _first = n;
        return item;
    }

    [[nodiscard]] bool
    empty() const override
    {
        return (_first == nullptr);
    }

private:
    struct Node {
        Node(const T& item, Node* next)
            : item{item}
            , next{next}
        {
        }

        T item;
        Node* next;
    };

private:
    Node* _first;
};

} // namespace algorithms
