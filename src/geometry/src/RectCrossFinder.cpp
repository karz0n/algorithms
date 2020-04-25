#include "RectCrossFinder.hpp"

#include "IntervalSearchTree.hpp"

namespace algorithms {

void
RectCrossFinder::add(const Rect& rect)
{
    _events.push(Event{rect, rect.p1.x /* Top Left  */});
    _events.push(Event{rect, rect.p3.x /* Top Right */});
}

void
RectCrossFinder::clear()
{
    _events.clear();
}

RectCrossFinder::RectPairs
RectCrossFinder::find()
{
    if (_events.empty()) {
        return {};
    }

    IntervalSearchTree<float, Rect> tree;
    RectPairs pairs;
    while (!_events.empty()) {
        const auto e = _events.pop();

        if (e.isLeft()) {
            auto [min, max] = std::minmax(e.rect.p1.y, e.rect.p2.y);
            auto rect = tree.intersects(min, max);
            if (rect.has_value()) {
                pairs.emplace_back(rect.value(), e.rect);
            }
            tree.put(min, max, e.rect);
            continue;
        }

        if (e.isRight()) {
            auto [min, max] = std::minmax(e.rect.p1.y, e.rect.p2.y);
            tree.erase(min, max);
        }
    }
    return pairs;
}

} // namespace algorithms
