#include "Percolation.hpp"

#include <stdexcept>

namespace algorithms
{
namespace uf
{

Percolation::Percolation(std::size_t number)
    : _width{0}
    , _count{0}
{
    reset(number);
}

void Percolation::reset(std::size_t number)
{
    _width = number;
    _count = number * number;

    _percolateModel = std::vector(_count, false);

    // Create connectivity model with two virtual sites (top and bottom).
    //
    _connectivityModel.reset(_count + 2);

    // Connect top site with all sites from the first row.
    //
    for (std::size_t i = 1; i <= number; ++i) {
        _connectivityModel.associate(0, i);
    }

    // Connect bottom site with all sites from the last row.
    //
    for (std::size_t i = _count - number + 1; i <= _count; ++i) {
        _connectivityModel.associate(_count + 1, i);
    }
}

void Percolation::open(std::size_t site)
{
#ifndef NDEBUG
    validate(site);
#endif
    _percolateModel[site] = true;

    connect(site, site - _width);
    connect(site, site + _width);

    if (site % _width != 0)
    {
        connect(site, site - 1);
    }

    if (site % _width != _width - 1)
    {
        connect(site, site + 1);
    }
}

bool Percolation::isOpened(std::size_t site)
{
    return _percolateModel[site];
}

std::size_t Percolation::width() const
{
    return _width;
}

std::size_t Percolation::totalCount() const
{
    return _count;
}

std::size_t Percolation::countOfOpened() const
{
    std::size_t opened = 0;
    for (std::size_t i = 0; i < _count; ++i) {
        if (_percolateModel[i]) {
            opened++;
        }
    }
    return opened;
}

bool Percolation::isPercolated()
{
    return _connectivityModel.connected(0, _count - 1);
}

#ifndef NDEBUG
void Percolation::validate(std::size_t site) const
{
    std::size_t size = _percolateModel.size();
    if (site >= size) {
        throw std::out_of_range(
                    "Index " + std::to_string(site) + " is not between 0 and " + std::to_string(size - 1));
    }
}
#endif

void Percolation::connect(int p, int q)
{
    if (p < 0 || p >= _percolateModel.size()) return;
    if (q < 0 || q >= _percolateModel.size()) return;

    if (_percolateModel[p] && _percolateModel[q]) {
        if (!_connectivityModel.connected(p, q)) {
            _connectivityModel.associate(p, q);
        }
    }
}

}
}
