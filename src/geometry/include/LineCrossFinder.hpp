#pragma once

#include "Points.hpp"
#include "LineSegment.hpp"

#include <PriorityQueue.hpp>

namespace algorithms {

/**
 * Find intersection points between orthogonal segments.
 *
 * Important: Segments have to be orthogonal. In other word
 *            each segment should be vertical or horizontal.
 */
class LineCrossFinder {
public:
    void
    add(const LineSegment& segment);

    void
    clear();

    Points
    find();

private:
    struct Event {
        Event(const LineSegment& s, float time)
            : segment{s}
            , time{time}
        {
        }

        bool
        isLeft() const
        {
            return std::abs(time - segment.p1.x) < std::numeric_limits<float>::epsilon();
        }

        bool
        isRight() const
        {
            return std::abs(time - segment.p2.x) < std::numeric_limits<float>::epsilon();
        }

        bool
        operator<(const Event& other) const
        {
            return time < other.time;
        }

        bool
        operator>(const Event& other) const
        {
            return time > other.time;
        }

        LineSegment segment;
        float time;
    };

private:
    MinPriorityQueue<Event> _events;
};

} // namespace algorithms
