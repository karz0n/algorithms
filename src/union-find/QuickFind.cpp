#include "QuickFind.hpp"

#include <algorithm>
#include <string>
#include <utility>
#include <stdexcept>

namespace algorithms
{
namespace uf
{

QuickFind::QuickFind()
    : _count(0)
{ }

QuickFind::QuickFind(std::size_t size)
{
    reset(size);
}

QuickFind::QuickFind(QuickFind&& other)
    : _parent(std::move(other._parent))
    , _count(other._count)
{
    other._count = 0;
}

QuickFind& QuickFind::operator=(QuickFind&& other)
{
    if (this != &other) {
        std::swap(_parent, other._parent);
        std::swap(_count, other._count);
    }
    return *this;
}

std::size_t QuickFind::find(std::size_t p) const
{
#ifndef NDEBUG
    validate(p);
#endif
    return _parent[p];
}

std::size_t QuickFind::count() const
{
    return _count;
}

void QuickFind::reset(std::size_t count)
{
    _count = count;
    _parent.resize(count);
    for (auto i = 0; i < count; ++i) {
        _parent[i] = i;
    }
}

bool QuickFind::connected(std::size_t p, std::size_t q) const
{
#ifndef NDEBUG
    validate(p);
    validate(q);
#endif
    return _parent[p] == _parent[q];
}

void QuickFind::associate(std::size_t p, std::size_t q)
{
#ifndef NDEBUG
    validate(p);
    validate(q);
#endif
    std::size_t proot = _parent[p];
    std::size_t qroot = _parent[q];
    if (proot == qroot) {
        return;
    }

    std::replace(_parent.begin(), _parent.end(), proot, qroot);

    _count--;
}

#ifndef NDEBUG
void QuickFind::validate(std::size_t p) const
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
