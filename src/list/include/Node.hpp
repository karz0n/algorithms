#pragma once

namespace algorithms {

template<typename T>
struct Node {
    explicit Node(const T& item)
        : item{item}
        , next{nullptr}
        , prev{nullptr}
    {
    }

    Node(const Node& other)
        : item{other.item}
        , next{other.next}
        , prev{other.prev}
    {
    }

    T item;
    Node* next;
    Node* prev;
};

} // namespace algorithms
