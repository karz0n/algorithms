#ifndef EVENT_HPP
#define EVENT_HPP

#include "Particle.hpp"

namespace algorithms {

class Event
{
public:
    Event(double time, Particle::OptionalRef p1, Particle::OptionalRef p2);

    bool operator<(const Event&) const;

    bool operator>(const Event&) const;

    int compare(const Event& other) const;

    bool hasA() const;
    bool hasB() const;

    Particle& getA();
    const Particle& getA() const;

    Particle& getB();
    const Particle& getB() const;

    double getTime() const;

    bool isValid() const;

private:
    double _time;
    Particle::OptionalRef _pA;
    Particle::OptionalRef _pB;
    int _countA;
    int _countB;
};

} // namespace algorithms

#endif // EVENT_HPP
