#include "UnionFind.hpp"

#include <algorithm>
#include <utility>
#include <stdexcept>

namespace algorithms
{
namespace uf
{

UnionFind::UnionFind()
    : _count{0}
{ }

UnionFind::UnionFind(std::size_t count)
{
    reset(count);
}

UnionFind::UnionFind(UnionFind&& other)
    : _container{std::move(other._container)}
    , _size{std::move(other._size)}
    , _count{other._count}
{
    other._count = 0;
}

UnionFind& UnionFind::operator=(UnionFind&& other)
{
    if (this != &other) {
        std::swap(_container, other._container);
        std::swap(_size, other._size);
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
    while (root != _container[root]) {
        root = _container[root];
    }

    // Compress the path
    while (p != root) {
        std::size_t np = _container[p];
        _container[p] = root;
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
    _container.resize(count);
    _size.resize(count);
    for (auto i = 0; i < count; ++i) {
        _container[i] = i;
        _size[i] = 1;
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
    if (_size[proot] < _size[qroot]) {
        _container[proot] = qroot;
        _size[qroot] += _size[proot];
    }
    else {
        _container[qroot] = proot;
        _size[proot] += _size[qroot];
    }

    _count--;
}

#ifndef NDEBUG
void UnionFind::validate(std::size_t p) const
{
    std::size_t size = _container.size();
    if (p >= size) {
        throw std::out_of_range(
                    "index " + std::to_string(p) + " is not between 0 and " + std::to_string(size - 1));
    }
}
#endif

} // namespace uf
} // namespace algorithms
