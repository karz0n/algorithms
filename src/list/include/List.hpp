#pragma once

namespace algorithms {

template<typename T>
class List {
public:
    virtual ~List() = default;

    virtual T&
    front()
        = 0;

    virtual const T&
    front() const = 0;

    virtual T&
    back()
        = 0;

    virtual const T&
    back() const = 0;

    virtual void
    pushFront(const T&)
        = 0;

    virtual T
    popFront()
        = 0;

    virtual void
    pushBack(const T&)
        = 0;

    virtual T
    popBack()
        = 0;

    [[nodiscard]] virtual bool
    empty() const = 0;
};

} // namespace algorithms
