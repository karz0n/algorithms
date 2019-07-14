#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include <stdexcept>

#include "Queue.hpp"

namespace algorithms {

template <typename T>
class LinkedQueue : public Queue<T> {
public:
    LinkedQueue()
        : _first{nullptr}
        , _last{nullptr}
        , _size{0}
    {
    }

    ~LinkedQueue()
    {
        Node* n = nullptr;
        while (_first) {
            n = _first->next;
            delete _first;
            _first = n;
        }
    }

    void push(const T& item) override
    {
        Node* n = _last;
        _last = new Node(item);
        if (empty()) {
            _first = _last;
        }
        else {
            n->next = _last;
        }
        _size++;
    }

    T pop() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        Node* n = _first;
        _first = n->next;
        T item = n->value;
        delete n;
        _size--;
        return item;
    }

    T& front() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _first->value;
    }

    const T& front() const override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _first->value;
    }

    T& back() override
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _last->value;
    }

    const T& back() const
    {
#ifndef NDEBUG
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
#endif
        return _last->value;
    }

    bool empty() const override
    {
        return (_size == 0);
    }

    std::size_t size() const override
    {
        return _size;
    }

private:
    struct Node {
        Node(const T& value)
            : value{value}
            , next{nullptr}
        {
        }

        T value;
        Node* next;
    };

private:
    Node* _first;
    Node* _last;
    std::size_t _size;
};

} // namespace algorithms

#endif // LINKEDQUEUE_HPP
