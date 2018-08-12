#ifndef QUICKUNION_HPP
#define QUICKUNION_HPP

#include <vector>

namespace algorithms
{
namespace uf
{

/**
 * The {@code QuickUnion} class represents a <em>union–find data type</em>
 * (also known as the <em>disjoint-sets data type</em>).
 * It supports the @em associate and @em find operations,
 * along with a @em connected operation for determining whether
 * two sites are in the same component and a @em count operation that
 * returns the total number of components.
 *
 * The union–find data type models connectivity among a set of @em n
 * sites, named 0 through @em n – 1.
 * The <em>is-connected-to</em> relation must be an
 * <em>equivalence relation</em>:
 *  -# @em Reflexive: @em p is connected to @em p.
 *  -# @em Symmetric: If @em p is connected to @em q,
 *     then @em q is connected to @em p.
 *  -# @em Transitive: If @em p is connected to @em q
 *     and @em q is connected to @em r, then
 *     @em p is connected to @em r.
 *
 * An equivalence relation partitions the sites into
 * <em>equivalence classes</em> (or @em components). In this case,
 * two sites are in the same component iff they are connected.
 * Both sites and components are identified with integers between 0 and
 * @em n – 1.
 * Initially, there are @em n components, with each site in its
 * own component.  The <em>component identifier</em> of a component
 * is one of the sites in the component:
 *  -# two sites have the same component identifier iff they are
 *     in the same component.
 * The component identifier of a component can change
 * only when the component itself changes during a call to
 * @em associate it cannot change during a call
 * to @em find, @em connected, or @em count.
 *
 * This implementation uses quick union.
 *
 * Cost model:
 *  - initalize: N
 *  - union: N* (includes cost of finding root)
 *  - find: N (in worst case)
 *
 * Defects:
 *  * tree can get tall.
 *  * find operation too expensive (could be N array accesses in
 *    case of tall tree).
 *
 * Worst-case time: M x N (M union-find operations on a set of N objects).
 *
 * Materials has obtained from:
 *  "Algorithms: 24-part Lecture Series by Robert Sedgewick and Kevin Wayne"
 */
class QuickUnion
{
public:
    /**
     * Default ctor.
     */
    QuickUnion();

    /**
     * Construct object with given count of sites.
     *
     * @param count the number of sites.
     *
     * @see reset
     */
    QuickUnion(std::size_t count);

    /**
     * Move ctor.
     */
    QuickUnion(QuickUnion&&);

    /**
     * Move assign operator.
     */
    QuickUnion& operator=(QuickUnion&&);

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
     * Takes constant time.
     *
     * @param p he integer representing one site.
     * @return the component identifier of the component containing @em p.
     */
    std::size_t find(std::size_t p) const;

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
     * Takes linear time from N. Where N is a number of sites.
     *
     * @param p the integer representing one site.
     * @param q the integer representing another site.
     * @return \c true iif the two sites @em p and @em q are in the
     *         same component, \c false otherwise.
     */
    bool connected(std::size_t p, std::size_t q) const;

    /**
     * Adds a connection between the two sites @em p and @em q.
     * If @em p and @em q are in different components,
     * then it replaces these two components with a new component
     * that is the union of the two.
     *
     * Takes linear time from N (includes cost of finding roots).
     * Where N is a number of sites.
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
    std::vector<std::size_t> _parent;
    std::size_t _count;
};

} // namespace uf
} // namespace algorithms

#endif // QUICKUNION_HPP
