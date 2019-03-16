#include "CollisionSystem.hpp"

namespace algorithms {

const double TIME_TO_PAUSE = 30;
const double HZ = 0.5; /** number of redraw events per clock tick */

const double CollisionSystem::UNLIMITED = std::numeric_limits<double>::infinity();

CollisionSystem::CollisionSystem(std::size_t count, double limit /*= UNLIMITED*/)
    : _time{0.0}
    , _limit{limit}
{
    for (std::size_t i = 0; i < count; ++i) {
        _particles.emplace_back(*this);
    }
}

void CollisionSystem::init()
{
    for (auto& particle : _particles) {
        predict(particle);
    }

    _events.enqueue(Event{0.0, Particle::OptionalRef{}, Particle::OptionalRef{}});
}

void CollisionSystem::draw()
{
    while (!_events.empty())
    {
        auto event = _events.dequeue();
        if (!event.isValid()) {
            continue;
        }

        for (auto& particle : _particles) {
            double dt = event.getTime() - _time;
            particle.move(dt);
        }
        _time = event.getTime();

        if (event.hasA() && event.hasB()) {
            event.getA().bounceOff(event.getB());
        }
        else if (event.hasA() && !event.hasB()) {
            event.getA().bounceOffVerticalWall();
        }
        else if (!event.hasA() && event.hasB()) {
            event.getB().bounceOffHorizontalWall();
        }
        else {
            redraw();
            postpone(TIME_TO_PAUSE);
            return;
        }

        if (event.hasA()) {
            predict(event.getA());
        }
        if (event.hasB()) {
            predict(event.getB());
        }
    }
}

void CollisionSystem::predict(Particle& target)
{
    for (auto& particle : _particles) {
        double dt = target.timeToHit(particle);
        if (_time + dt <= _limit) {
            _events.enqueue(Event{_time + dt, Particle::OptionalRef{target}, Particle::OptionalRef{particle}});
        }
    }

    double dtX = target.timeToHitVerticalWall();
    if (_time + dtX <= _limit) {
        _events.enqueue(Event{_time + dtX, Particle::OptionalRef{target}, Particle::OptionalRef{}});
    }

    double dtY = target.timeToHitHorizontalWall();
    if (_time + dtY) {
        _events.enqueue(Event{_time + dtY, Particle::OptionalRef{}, Particle::OptionalRef{target}});
    }
}

void CollisionSystem::redraw()
{
    clear();

    for (auto& particle : _particles) {
        particle.draw();
    }

    if (_time < _limit) {
        _events.enqueue(Event{_time + 1.0 / 0.5, Particle::OptionalRef{}, Particle::OptionalRef{}});
    }

    swapBuffers();
}

} // namespace algorithms
