#include "QuickFind.hpp"

#include <numeric>
#include <algorithm>
#include <string>
#include <utility>
#include <stdexcept>

namespace algorithms {

QuickFind::QuickFind()
    : _count{0}
{
}

QuickFind::QuickFind(std::size_t size)
    : _count{0}
{
    reset(size);
}

QuickFind::QuickFind(QuickFind&& other) noexcept
    : _container{std::move(other._container)}
    , _count{other._count}
{
    other._count = 0;
}

QuickFind&
QuickFind::operator=(QuickFind&& other)
{
    if (this != &other) {
        std::swap(_container, other._container);
        std::swap(_count, other._count);
    }
    return *this;
}

std::size_t
QuickFind::find(std::size_t p) const
{
#ifndef NDEBUG
    validate(p);
#endif
    return _container[p];
}

std::size_t
QuickFind::count() const
{
    return _count;
}

void
QuickFind::reset(std::size_t count)
{
    _container.resize(_count = count);
    std::iota(_container.begin(), _container.end(), 0);
}

bool
QuickFind::connected(std::size_t p, std::size_t q) const
{
#ifndef NDEBUG
    validate(p);
    validate(q);
#endif
    return _container[p] == _container[q];
}

void
QuickFind::associate(std::size_t p, std::size_t q)
{
#ifndef NDEBUG
    validate(p);
    validate(q);
#endif
    std::size_t proot = _container[p];
    std::size_t qroot = _container[q];
    if (proot == qroot) {
        return;
    }
    std::replace(_container.begin(), _container.end(), proot, qroot);
    _count--;
}

#ifndef NDEBUG
void
QuickFind::validate(std::size_t n) const
{
    std::size_t size = _container.size();
    if (n >= size) {
        throw std::out_of_range("Index " + std::to_string(n) + " is not between 0 and "
                                + std::to_string(size - 1));
    }
}
#endif

} // namespace algorithms
