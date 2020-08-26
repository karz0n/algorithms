#include "QuickUnion.hpp"

#include <numeric>
#include <string>
#include <utility>
#include <stdexcept>

namespace algorithms {

QuickUnion::QuickUnion()
    : _count{0}
{
}

QuickUnion::QuickUnion(std::size_t count)
    : _count{0}
{
    reset(count);
}

QuickUnion::QuickUnion(QuickUnion&& other) noexcept
    : _container{std::move(other._container)}
    , _count{other._count}
{
    other._count = 0;
}

QuickUnion&
QuickUnion::operator=(QuickUnion&& other)
{
    if (this != &other) {
        std::swap(_container, other._container);
        std::swap(_count, other._count);
    }
    return *this;
}

std::size_t
QuickUnion::find(std::size_t p) const
{
#ifndef NDEBUG
    validate(p);
#endif
    while (p != _container[p]) {
        p = _container[p];
    }
    return p;
}

std::size_t
QuickUnion::count() const
{
    return _count;
}

void
QuickUnion::reset(std::size_t count)
{
    _container.resize(_count = count);
    std::iota(_container.begin(), _container.end(), 0);
}

bool
QuickUnion::connected(std::size_t p, std::size_t q) const
{
    return find(p) == find(q);
}

void
QuickUnion::associate(std::size_t p, std::size_t q)
{
    std::size_t proot = find(p);
    std::size_t qroot = find(q);
    if (proot == qroot) {
        return;
    }
    _container[proot] = qroot;
    _count--;
}

#ifndef NDEBUG
void
QuickUnion::validate(std::size_t p) const
{
    std::size_t size = _container.size();
    if (p >= size) {
        throw std::out_of_range("index " + std::to_string(p) + " is not between 0 and "
                                + std::to_string(size - 1));
    }
}
#endif

} // namespace algorithms
