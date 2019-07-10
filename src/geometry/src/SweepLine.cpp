#include "SweepLine.hpp"

#include <stdexcept>
#include <set>
#include <limits>

#include <PriorityQueue.hpp>

static constexpr double MIN_X = std::numeric_limits<double>::min();
static constexpr double MAX_X = std::numeric_limits<double>::max();

namespace algorithms {

struct Event {
    Event(double time, const Segment& s)
        : time{time}
        , segment{s}
    {
    }

    double time;
    Segment segment;
};

struct EventComparator {
    bool operator()(const Event& e1, const Event& e2) const
    {
        return e1.time > e2.time;
    }
};

struct OrthogonalSegmentComparator {
    bool operator()(const Segment& s1, const Segment& s2) const
    {
        if (s1.p1.y < s2.p1.y || s1.p2.y < s2.p2.y) {
            return true;
        }
        if (s1.p1.y > s2.p1.y || s1.p2.y > s2.p2.y) {
            return false;
        }
        if (s1.p1.x < s2.p1.x || s1.p2.x < s2.p2.x) {
            return true;
        }
        if (s1.p1.x > s2.p1.x || s1.p2.x > s2.p2.x) {
            return false;
        }
        return false;
    }
};

Points orthogonalSegmentIntersection(const Segments& segments)
{
    Points points;

    MinPriorityQueue<Event, EventComparator> events;
    for (const auto& segment : segments) {
        if (segment.isVertical()) {
            events.enqueue(Event{segment.p1.x, segment});
            continue;
        }
        if (segment.isHorizontal()) {
            events.enqueue(Event{segment.p1.x, segment});
            events.enqueue(Event{segment.p2.x, segment});
            continue;
        }
        throw std::logic_error{"Segment should be vertical or horizontal"};
    }

    std::set<Segment, OrthogonalSegmentComparator> set;
    while (!events.empty()) {
        auto e = events.dequeue();

        if (e.segment.isVertical()) {
            Segment s1{Point{MIN_X, e.segment.p1.y}, Point{MIN_X, e.segment.p1.y}};
            Segment s2{Point{MAX_X, e.segment.p2.y}, Point{MAX_X, e.segment.p2.y}};
            auto it1 = set.lower_bound(s1);
            auto it2 = set.upper_bound(s2);
            std::for_each(it1, it2, [&e, &points](const auto& s) { points.emplace_back(e.segment.p1.x, s.p1.y); });
            continue;
        }

        if (e.time == e.segment.p1.x) {
            set.insert(e.segment);
            continue;
        }

        if (e.time == e.segment.p2.x) {
            set.erase(e.segment);
        }
    }

    return points;
}

} // namespace algorithms
