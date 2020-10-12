#include "LineCrossFinder.hpp"

#include <set>
#include <stdexcept>

namespace algorithms {

void
LineCrossFinder::add(const LineSegment& segment)
{
    if (segment.isVertical()) {
        _events.push(Event{segment, segment.p1.x});
        return;
    }

    if (segment.isHorizontal()) {
        _events.push(Event{segment, segment.p1.x});
        _events.push(Event{segment, segment.p2.x});
        return;
    }

    throw std::logic_error{"Line segment has to be orthogonal"};
}

void
LineCrossFinder::clear()
{
}

Points
LineCrossFinder::find()
{
    static const float MIN_X = std::numeric_limits<float>::min();
    static const float MAX_X = std::numeric_limits<float>::max();

    Points points;

    std::set<LineSegment> set;
    while (!_events.empty()) {
        const auto e = _events.pop();

        if (e.segment.isVertical()) {
            LineSegment lower{Point{MIN_X, e.segment.p1.y}, Point{MIN_X, e.segment.p1.y}};
            LineSegment upper{Point{MAX_X, e.segment.p2.y}, Point{MAX_X, e.segment.p2.y}};
            auto it1 = set.lower_bound(lower);
            auto it2 = set.upper_bound(upper);
            std::for_each(
                it1, it2, [&](const auto& s) { points.emplace_back(e.segment.p1.x, s.p1.y); });
            continue;
        }

        if (e.isLeft()) {
            set.insert(e.segment);
            continue;
        }

        if (e.isRight()) {
            set.erase(e.segment);
        }
    }

    return points;
}

} // namespace algorithms
