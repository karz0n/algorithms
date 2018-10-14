#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include <stdexcept>

#include "Stack.hpp"

namespace algorithms {

/**
 *
 */
template<typename T>
class LinkedStack : public Stack<T> {
public:
    LinkedStack()
        : _first{nullptr}
    { }

    void push(const T& item) override
    {
        Node* p = _first;
        _first = new Node{item, p};
    }

    T pop() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
#endif
        T item = _first->item;
        delete _first;
        _first = _first->next;
        return item;
    }

    bool isEmpty() const override
    {
        return (_first == nullptr);
    }

private:
    struct Node {
        Node(const T& item, Node* next)
            : item{item}
            , next{next}
        { }

        T item;
        Node* next;
    };

private:
    Node* _first;
};

} // namespace algorithms

#endif // LINKEDSTACK_HPP
