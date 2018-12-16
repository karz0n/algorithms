#ifndef COMPARATORS_HPP
#define COMPARATORS_HPP

#include "Point.hpp"

namespace algorithms {

/**
 *
 */
class Comparator {
public:
    virtual ~Comparator() = default;

    int operator()(const Point& p1, const Point& p2) const
    {
        return compare(p1, p2);
    }

    virtual int compare(const Point& p1, const Point& p2) const = 0;
};

/**
 *
 */
class PolarOrder : public Comparator {
public:
    PolarOrder(const Point& base);

    int compare(const Point& p1, const Point& p2) const override;

private:
    Point _base;
};

/**
 *
 */
class Comparators
{
public:
    static PolarOrder byPolarOrder(const Point& base);
};

} // namespace algorithms

#endif // COMPARATORS_HPP
