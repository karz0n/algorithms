#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <vector>

#include "UnionFind.hpp"

namespace algorithms
{
namespace uf
{

/**
 * Connectivity model type.
 *
 * This model represented by union find class algorithm.
 */
using ConnectivityModel = UnionFind;

/**
 * Percolation model type.
 *
 * This model represented by simple sequence of bool values.
 */
using PercolateModel = std::vector<bool>;

/**
 * Percolation class.
 *
 * This class represents the way to use union find algorithm which
 * let us to determine if the model is percolated.
 * Percolated model is the model where the top of this model connected
 * to the bottom through open sites.
 */
class Percolation {
public:
    /**
     * Default ctor.
     *
     * @param width The width of model.
     */
    Percolation(std::size_t width);

    /**
     * Resets model wih given width.
     *
     * @param width The width of model.
     */
    void reset(std::size_t width);

    /**
     * Opens given site.
     *
     * @param site The site which need to be open.
     */
    void open(std::size_t site);

    /**
     * Check is given site is open.
     *
     * @param site The number of site.
     *
     * @return The open state of given site.
     */
    bool isOpened(std::size_t site);

    /**
     * Returns the width of percolation model.
     *
     * @return The width of percolation model.
     */
    std::size_t width() const;

    /**
     * Returns the total number of sites.
     *
     * @return The total number of sites.
     */
    std::size_t totalCount() const;

    /**
     *
     * @return
     */
    std::size_t countOfOpened() const;

    /**
     * Returns the percolation status of model.
     *
     * @return The status of model.
     */
    bool isPercolated();

private:
#ifndef NDEBUG
    void validate(std::size_t n) const;
#endif
    void connect(int p, int q);
private:
    std::size_t _width;
    std::size_t _count;
    PercolateModel _percolateModel;
    ConnectivityModel _connectivityModel;
};

}
}

#endif // PERCOLATION_HPP
