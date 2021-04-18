#pragma once

#include "Points.hpp"

namespace algorithms {

class GrahamScan {
public:
    GrahamScan() = default;

    explicit GrahamScan(const Points& points);

    void
    scan(Points points);

    [[nodiscard]] const Points&
    hull() const;

private:
    Points _hull;
};

//
// Inlines
//

inline const Points&
GrahamScan::hull() const
{
    return _hull;
}

} // namespace algorithms