#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include <vector>

namespace algorithms
{
namespace uf
{

/**
 * The {@code UnionFind} class represents a
 * union–find data structure.
 * It supports the @em associate and @em find operations,
 * along with a @em connected operation for determining whether
 * two sites are in the same component and a @em count operation that
 * returns the total number of components.
 *
 * This implementation uses weighted quick union with full path
 * compression and has next cost model:
 *  - initalize: N
 *  - union: lg N (includes cost of finding root)
 *  - find: lg N
 *
 * Worst-case time: N + M x lg* N (M union-find operations on a set of
 * N objects) and lg* is iterated logarithm.
 *
 * Materials has obtained from:
 *  "Algorithms: 24-part Lecture Series by Robert Sedgewick and Kevin Wayne"
 */
class UnionFind
{
public:
    /**
     * Default ctor.
     */
    UnionFind();

    /**
     * Construct object with given count of sites.
     *
     * @param count the number of sites.
     *
     * @see reset
     */
    UnionFind(std::size_t count);

    /**
     * Move ctor.
     */
    UnionFind(UnionFind&&);

    /**
     * Move assign operator.
     */
    UnionFind& operator=(UnionFind&&);

    /**
     * Initialize with given count of sites.
     *
     * Initializing takes linear time from N.
     * Where N is a number of sites.
     *
     * @param count the number of sites.
     */
    void reset(std::size_t count);

    /**
     * Finds @em p and returns the component
     * identifier of the component containing @em p.
     *
     * Takes time equals logarithm with base 2 from N.
     * Where N is a number of sites.
     *
     * As you can this method now doesn't have const qualifier
     * because it does path compression.
     *
     * @param p he integer representing one site.
     *
     * @return the component identifier of the component containing @em p.
     */
    std::size_t find(std::size_t p);

    /**
     * Returns the number of components.
     *
     * Takes constant time.
     *
     * @return the number of components.
     */
    std::size_t count() const;

    /**
     * Returns \c true if both @em p and @em q
     * are in the same component, and \c false otherwise.
     *
     * Takes time equals logarithm with base 2 from N.
     * Where N is a number of sites.
     *
     * @param p the integer representing one site.
     * @param q the integer representing another site.
     *
     * @return \c true iif the two sites @em p and @em q are in the
     *         same component, \c false otherwise.
     */
    bool connected(std::size_t p, std::size_t q);

    /**
     * Adds a connection between the two sites @em p and @em q.
     * If @em p and @em q are in different components,
     * then it replaces these two components with a new component
     * that is the union of the two.
     *
     * Takes time equals logarithm with base 2 from N (includes
     * cost of finding roots). Where N is a number of sites.
     *
     * @param p the integer representing one site.
     * @param q the integer representing another site.
     */
    void associate(std::size_t p, std::size_t q);

#ifndef NDEBUG
private:
    void validate(std::size_t p) const;
#endif
private:
    std::vector<std::size_t> _container;
    std::vector<std::size_t> _size;
    std::size_t _count;
};

} // namespace uf
} // namespace algorithms

#endif // UNIONFIND_HPP
