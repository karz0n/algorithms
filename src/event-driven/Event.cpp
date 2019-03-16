#include "Event.hpp"

namespace algorithms {

Event::Event(double time, Particle::OptionalRef p1, Particle::OptionalRef p2)
    : _time{time}
    , _pA{p1}
    , _pB{p2}
    , _countA{p1.has_value() ? p1->get().count() : -1}
    , _countB{p2.has_value() ? p2->get().count() : -1}
{
}

bool Event::operator<(const Event& other) const
{
    return (_time < other._time);
}

bool Event::operator>(const Event& other) const
{
    return (_time > other._time);
}

int Event::compare(const Event &other) const
{
    if (*this < other) {
        return -1;
    }
    if (other < *this) {
        return +1;
    }
    return 0;
}

bool Event::hasA() const
{
    return _pA.has_value();
}

bool Event::hasB() const
{
    return _pB.has_value();
}

Particle &Event::getA()
{
    return _pA.value().get();
}

const Particle &Event::getA() const
{
    return _pA.value().get();
}

Particle &Event::getB()
{
    return _pB.value().get();
}

const Particle &Event::getB() const
{
    return _pB.value().get();
}

double Event::getTime() const
{
    return _time;
}

bool Event::isValid() const
{
    /** Checks if one of particle collide with third party particles or walls */
    if (_pA.has_value() && _pA->get().count() != _countA) return false;
    if (_pB.has_value() && _pB->get().count() != _countB) return false;
    return true;
}

} // namespace algorithms
