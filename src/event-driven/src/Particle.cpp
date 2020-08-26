#include "Particle.hpp"

#include <algorithm>
#include <limits>
#include <random>

namespace algorithms {

constexpr double DefaultMinVx = -0.01;
constexpr double DefaultMaxVx = 0.01;
constexpr double DefaultMinVy = -0.01;
constexpr double DefaultMaxVy = 0.01;
constexpr double DefaultRadius = 0.05;
constexpr double DefaultMass = 0.5;

Particle::Particle(DrawArea& area)
    : DrawObject{area}
{
    std::random_device rd;
    std::mt19937 gen(rd());

    _rx = std::uniform_real_distribution<>{getXMin(), getXMax()}(gen);
    _ry = std::uniform_real_distribution<>{getYMin(), getYMax()}(gen);
    _vx = std::uniform_real_distribution<>{DefaultMinVx, DefaultMaxVx}(gen);
    _vy = std::uniform_real_distribution<>{DefaultMinVy, DefaultMaxVy}(gen);
    _radius = DefaultRadius;
    _mass = DefaultMass;
    _count = 0;
}

Particle::Particle(DrawArea& area, double radius, double mass, double vx, double vy, double rx,
                   double ry)
    : DrawObject{area}
    , _radius{radius}
    , _mass{mass}
    , _rx{rx}
    , _ry{ry}
    , _vx{vx}
    , _vy{vy}
    , _count{0}
{
}

void
Particle::move(double dt)
{
    _rx += _vx * dt;
    _ry += _vy * dt;
}

void
Particle::draw()
{
    DrawArea::drawCircle(_rx, _ry, _radius);
}

double
Particle::timeToHit(const Particle& other)
{
    if (this == &other) {
        return std::numeric_limits<double>::infinity();
    }

    double dx = other._rx - _rx;
    double dy = other._ry - _ry;
    double dvx = other._vx - _vx;
    double dvy = other._vy - _vy;

    double dvdr = dx * dvx + dy * dvy;
    if (dvdr > 0) {
        return std::numeric_limits<double>::infinity();
    }

    double dvdv = dvx * dvx + dvy * dvy;
    if (dvdv == 0.0) {
        return std::numeric_limits<double>::infinity();
    }

    double drdr = dx * dx + dy * dy;
    double sigma = _radius + other._radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    if (d < 0) {
        return std::numeric_limits<double>::infinity();
    }

    return -(dvdr + std::sqrt(d)) / dvdv;
}

double
Particle::timeToHitVerticalWall()
{
    if (_vx > 0) {
        return (getXMax() - _rx) / _vx;
    }
    else if (_vx < 0) {
        return (getXMin() - _rx) / _vx;
    }
    else {
        return std::numeric_limits<double>::infinity();
    }
}

double
Particle::timeToHitHorizontalWall()
{
    if (_vy > 0) {
        return (getYMax() - _ry) / _vy;
    }
    else if (_vy < 0) {
        return (getYMin() - _ry) / _vy;
    }
    else {
        return std::numeric_limits<double>::infinity();
    }
}

void
Particle::bounceOff(Particle& other)
{
    double dx = other._rx - _rx;
    double dy = other._ry - _ry;
    double dvx = other._vx - _vx;
    double dvy = other._vy - _vy;
    double dvdr = dx * dvx + dy * dvy;

    /** Distance between particle centers at collison */
    double dist = _radius + other._radius;

    /** Magnitude of normal force */
    double magnitude = 2 * _mass * other._mass * dvdr / ((_mass + other._mass) * dist);

    /** Normal force, and in x and y directions */
    double fx = magnitude * dx / dist;
    double fy = magnitude * dy / dist;

    /** Update velocities according to normal force */
    _vx += fx / _mass;
    _vy += fy / _mass;
    other._vx -= fx / other._mass;
    other._vy -= fy / other._mass;

    /** Update collision counts */
    _count++;
    other._count++;
}

void
Particle::bounceOffVerticalWall()
{
    _vx = -_vx;
    _count++;
}

void
Particle::bounceOffHorizontalWall()
{
    _vy = -_vy;
    _count++;
}

double
Particle::kineticEnergy() const
{
    return (0.5 * _mass * (_vx * _vx + _vy * _vy));
}

int
Particle::count() const
{
    return _count;
}

double
Particle::getXMax()
{
    return getArea().getClipAreaXRight() - double(_radius);
}

double
Particle::getXMin()
{
    return getArea().getClipAreaXLeft() + double(_radius);
}

double
Particle::getYMax()
{
    return getArea().getClipAreaYTop() - double(_radius);
}

double
Particle::getYMin()
{
    return getArea().getClipAreaYBottom() + double(_radius);
}

} // namespace algorithms
