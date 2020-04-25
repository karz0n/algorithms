#pragma once

#include "Rect.hpp"

#include <PriorityQueue.hpp>

#include <tuple>

namespace algorithms {

/**
 *
 */
class RectCrossFinder {
public:
    using RectPair = std::pair<Rect, Rect>;
    using RectPairs = std::vector<RectPair>;

    void
    add(const Rect& rect);

    void
    clear();

    RectPairs
    find();

private:
    struct Event {
        enum class Types {
            Left,
            Right
        };

        Event(const Rect& rect, float time)
            : rect{rect}
            , time{time}
        {
        }

        bool
        isLeft() const
        {
            return std::abs(time - rect.p1.x) < std::numeric_limits<float>::epsilon();
        }

        bool
        isRight() const
        {
            return std::abs(time - rect.p3.x) < std::numeric_limits<float>::epsilon();
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

        Rect rect;
        float time;
    };

private:
    MinPriorityQueue<Event> _events;
};

} // namespace algorithms
