#include "UnionFind.hpp"

#include <algorithm>
#include <utility>
#include <stdexcept>

namespace algorithms
{
namespace uf
{

UnionFind::UnionFind()
    : _count(0)
{ }

UnionFind::UnionFind(std::size_t count)
{
    reset(count);
}

UnionFind::UnionFind(UnionFind&& other)
    : _parent(std::move(other._parent))
    , _weight(std::move(other._weight))
    , _count(other._count)
{
    other._count = 0;
}

UnionFind& UnionFind::operator=(UnionFind&& other)
{
    if (this != &other) {
        std::swap(_parent, other._parent);
        std::swap(_weight, other._weight);
        std::swap(_count, other._count);
    }
    return *this;
}

std::size_t UnionFind::find(std::size_t p)
{
#ifndef NDEBUG
    validate(p);
#endif
    std::size_t root = p;

    // Finds root of p site
    while (root != _parent[root]) {
        root = _parent[root];
    }

    // Compress the path
    while (p != root) {
        std::size_t np = _parent[p];
        _parent[p] = root;
        p = np;
    }

    return root;
}

std::size_t UnionFind::count() const
{
    return _count;
}

void UnionFind::reset(std::size_t count)
{
    _parent.resize(count);
    _weight.resize(count);
    for (auto i = 0; i < count; ++i) {
        _parent[i] = i;
        _weight[i] = 1;
    }
}

bool UnionFind::connected(std::size_t p, std::size_t q)
{
    return find(p) == find(q);
}

void UnionFind::associate(std::size_t p, std::size_t q)
{
    std::size_t proot = find(p);
    std::size_t qroot = find(q);
    if (proot == qroot) {
        return;
    }

    // Make smaller root point to larger one
    if (_weight[proot] < _weight[qroot]) {
        _parent[proot] = qroot;
        _weight[qroot] += _weight[proot];
    }
    else {
        _parent[qroot] = proot;
        _weight[proot] += _weight[qroot];
    }

    _count--;
}

#ifndef NDEBUG
void UnionFind::validate(std::size_t p) const
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
