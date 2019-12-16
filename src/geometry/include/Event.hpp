#pragma once

#include <cmath>
#include <limits>

#include "Segment.hpp"

namespace algorithms {

class Event {
public:
    constexpr Event(const Segment& s, double time)
        : _segment{s}
        , _time{time}
    {
    }

    constexpr const Segment& segment() const
    {
        return _segment;
    }

    constexpr double time() const
    {
        return _time;
    }

    constexpr bool isLeft() const
    {
        return std::abs(_time - _segment.p1.x) < std::numeric_limits<double>::epsilon();
    }

    constexpr bool isRight() const
    {
        return std::abs(_time - _segment.p2.x) < std::numeric_limits<double>::epsilon();
    }

    constexpr bool operator<(const Event& other) const
    {
        return _time < other._time;
    }

private:
    Segment _segment;
    double _time;
};

} // namespace algorithms
