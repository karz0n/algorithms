#include "QuickUnion.hpp"

#include <string>
#include <utility>
#include <stdexcept>

namespace algorithms
{
namespace uf
{

QuickUnion::QuickUnion()
    : _count(0)
{ }

QuickUnion::QuickUnion(std::size_t count)
{
    reset(count);
}

QuickUnion::QuickUnion(QuickUnion&& other)
    : _parent(std::move(other._parent))
    , _count(other._count)
{
    other._count = 0;
}

QuickUnion& QuickUnion::operator=(QuickUnion&& other)
{
    if (this != &other) {
        std::swap(_parent, other._parent);
        std::swap(_count, other._count);
    }
    return *this;
}

std::size_t QuickUnion::find(std::size_t p) const
{
#ifndef NDEBUG
    validate(p);
#endif
    while (p != _parent[p]) {
        p = _parent[p];
    }
    return p;
}

std::size_t QuickUnion::count() const
{
    return _count;
}

void QuickUnion::reset(std::size_t count)
{
    _count = count;
    _parent.resize(count);
    for (auto i = 0; i < count; ++i) {
        _parent[i] = i;
    }
}

bool QuickUnion::connected(std::size_t p, std::size_t q) const
{
    return find(p) == find(q);
}

void QuickUnion::associate(std::size_t p, std::size_t q)
{
    std::size_t proot = find(p);
    std::size_t qroot = find(q);
    if (proot == qroot) {
        return;
    }

    _parent[proot] = qroot;

    _count--;
}

#ifndef NDEBUG
void QuickUnion::validate(std::size_t p) const
{
    std::size_t size = _parent.size();
    if (p >= size) {
        throw std::out_of_range(
                    "index " + std::to_string(p) + " is not between 0 and " + std::to_string(size - 1));
    }
}
#endif

} // namespace uf
} // namespace algorithms
