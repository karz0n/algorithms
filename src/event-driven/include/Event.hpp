#pragma once

#include "Particle.hpp"

namespace algorithms {

class Event {
public:
    Event(double time, Particle::OptionalRef p1, Particle::OptionalRef p2);

    bool
    operator<(const Event&) const;

    bool
    operator>(const Event&) const;

    [[nodiscard]] int
    compare(const Event& other) const;

    [[nodiscard]] bool
    hasA() const;
    [[nodiscard]] bool
    hasB() const;

    Particle&
    getA();
    [[nodiscard]] const Particle&
    getA() const;

    Particle&
    getB();
    [[nodiscard]] const Particle&
    getB() const;

    [[nodiscard]] double
    getTime() const;

    [[nodiscard]] bool
    isValid() const;

private:
    double _time;
    Particle::OptionalRef _pA;
    Particle::OptionalRef _pB;
    int _countA;
    int _countB;
};

} // namespace algorithms
