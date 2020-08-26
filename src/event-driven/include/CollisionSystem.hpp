#pragma once

#include <vector>
#include <limits>

#include <PriorityQueue.hpp>

#include "DrawArea.hpp"
#include "Particle.hpp"
#include "Event.hpp"

namespace algorithms {

class CollisionSystem : public DrawArea {
public:
    static const double Unlimited;

    explicit CollisionSystem(std::size_t count, double limit = Unlimited);

    void
    init() override;

    void
    draw() override;

private:
    void
    predict(Particle& target);

    void
    redraw();

private:
    double _time;
    double _limit;
    std::vector<Particle> _particles;
    MaxPriorityQueue<Event> _events;
};

} // namespace algorithms
