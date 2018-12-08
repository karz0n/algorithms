#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include <stdexcept>

#include "Queue.hpp"

namespace algorithms {

template<typename T>
class LinkedQueue : public Queue<T>
{
public:
    LinkedQueue()
        : _first{nullptr}
        , _last{nullptr}
    { }

    ~LinkedQueue()
    {
        while (_first) {
            Node* n = _first->next;
            delete _first;
            _first = n;
        }
    }

    void enqueue(const T& item) override
    {
        Node* p = _last;
        _last = new Node(item);
        if (isEmpty()) {
           _first = _last;
        }
        else {
           p->next = _last;
        }
    }

    T dequeue() override
    {
#ifndef NDEBUG
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
#endif
        T item = _first->item;
        _first = _first->next;
        return item;
    }

    bool isEmpty() const override
    {
        return (_first == nullptr);
    }

private:
    struct Node {
        Node(const T& item)
            : item{item}
            , next{nullptr}
        { }

        T item;
        Node* next;
    };

private:
    Node* _first;
    Node* _last;
};


} // namespace algorithms

#endif // LINKEDQUEUE_HPP
