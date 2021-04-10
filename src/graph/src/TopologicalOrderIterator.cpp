#include "TopologicalOrderIterator.hpp"

#include <iterator>

namespace algorithms {

TopologicalOrderIterator::TopologicalOrderIterator(const Digraph& graph)
{
    try {
        auto vertices = DepthFirstOrder(graph, true).reversePost();
        _vertices = std::make_shared<Vertices>(std::move(vertices));
        moveToBegin();
    } catch (...) {
        // Suppress exception if the given graph has cycle
    }
}

TopologicalOrderIterator::TopologicalOrderIterator(const EdgeWeightedDigraph& graph)
{
    try {
        _vertices = std::make_shared<Vertices>(DepthFirstOrder(graph, true).reversePost());
        moveToBegin();
    } catch (...) {
        // Suppress exception if the given graph has cycle
    }
}

bool
TopologicalOrderIterator::operator==(const TopologicalOrderIterator& other) const
{
    if (this != &other) {
        return (_it == other._it);
    }
    return true;
}

bool
TopologicalOrderIterator::operator!=(const TopologicalOrderIterator& other) const
{
    return !(*this == other);
}

TopologicalOrderIterator::value_type
TopologicalOrderIterator::operator--(int)
{
#ifndef NDEBUG
    if (!hasOrder()) {
        throw std::runtime_error{"No order is present"};
    }
#endif
    value_type value{*_it};
    std::advance(_it, -1);
    return value;
}

TopologicalOrderIterator&
TopologicalOrderIterator::operator--()
{
#ifndef NDEBUG
    if (!hasOrder()) {
        throw std::runtime_error{"No order is present"};
    }
#endif
    std::advance(_it, -1);
    return *this;
}

TopologicalOrderIterator::value_type
TopologicalOrderIterator::operator++(int)
{
#ifndef NDEBUG
    if (!hasOrder()) {
        throw std::runtime_error{"No order is present"};
    }
#endif
    value_type value{*_it};
    std::advance(_it, +1);
    return value;
}

TopologicalOrderIterator&
TopologicalOrderIterator::operator++()
{
#ifndef NDEBUG
    if (!hasOrder()) {
        throw std::runtime_error{"No order is present"};
    }
#endif
    std::advance(_it, +1);
    return *this;
}

TopologicalOrderIterator::value_type
TopologicalOrderIterator::operator*()
{
#ifndef NDEBUG
    if (!hasOrder()) {
        throw std::runtime_error{"No order is present"};
    }
#endif
    return *_it;
}

void
TopologicalOrderIterator::moveToBegin()
{
    if (hasOrder()) {
        _it = _vertices->cbegin();
    }
}

void
TopologicalOrderIterator::moveToEnd()
{
    if (hasOrder()) {
        _it = _vertices->cend();
    }
}

[[nodiscard]] bool
TopologicalOrderIterator::hasOrder() const
{
    return (_vertices.use_count() > 0);
}

TopologicalOrderIterator
begin(const TopologicalOrderIterator& it)
{
    TopologicalOrderIterator copy{it};
    copy.moveToBegin();
    return copy;
}

TopologicalOrderIterator
end(const TopologicalOrderIterator& it)
{
    TopologicalOrderIterator copy{it};
    copy.moveToEnd();
    return copy;
}

} // namespace algorithms
