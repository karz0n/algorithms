#include "SweepLine.hpp"

#include <stdexcept>
#include <set>
#include <limits>

#include <PriorityQueue.hpp>

#include "Event.hpp"

static constexpr double MIN_X = std::numeric_limits<double>::min();
static constexpr double MAX_X = std::numeric_limits<double>::max();

namespace algorithms {

Points
orthogonalSegmentIntersection(const Segments& segments)
{
    Points points;

    MinPriorityQueue<Event> events;
    for (const auto& segment : segments) {
        if (segment.isVertical()) {
            events.push(Event{segment, segment.p1.x});
            continue;
        }
        if (segment.isHorizontal()) {
            events.push(Event{segment, segment.p1.x});
            events.push(Event{segment, segment.p2.x});
            continue;
        }
        throw std::logic_error{"Segment should be vertical or horizontal"};
    }

    std::set<Segment> set;
    while (!events.empty()) {
        auto e = events.pop();

        if (e.segment().isVertical()) {
            Segment lower{Point{MIN_X, e.segment().p1.y}, Point{MIN_X, e.segment().p1.y}};
            Segment upper{Point{MAX_X, e.segment().p2.y}, Point{MAX_X, e.segment().p2.y}};
            auto it1 = set.lower_bound(lower);
            auto it2 = set.upper_bound(upper);
            std::for_each(it1, it2, [&](const auto& s) { points.emplace_back(e.segment().p1.x, s.p1.y); });
            continue;
        }

        if (e.isLeft()) {
            set.insert(e.segment());
            continue;
        }

        if (e.isRight()) {
            set.erase(e.segment());
        }
    }

    return points;
}

} // namespace algorithms
