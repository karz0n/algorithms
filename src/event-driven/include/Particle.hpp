#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <optional>
#include <functional>

#include "DrawObject.hpp"

namespace algorithms {

class Particle : public DrawObject
{
public:
    using Ref = std::reference_wrapper<Particle>;

    using OptionalRef = std::optional<Ref>;

    Particle(DrawArea &area);

    Particle(DrawArea& area,
             double radius,
             double mass,
             double vx, double vy,
             double rx, double ry);

    void move(double dt);

    void draw();

    double timeToHit(const Particle& other);

    double timeToHitVerticalWall();

    double timeToHitHorizontalWall();

    void bounceOff(Particle& other);

    void bounceOffVerticalWall();

    void bounceOffHorizontalWall();

    double kineticEnergy() const;

    int count() const;

private:
    double getXMax();

    double getXMin();

    double getYMax();

    double getYMin();

private:
    double _radius;
    double _mass;
    double _rx;
    double _ry;
    double _vx;
    double _vy;
    int _count;
};

} // namespace algorithms

#endif // PARTICLE_HPP
