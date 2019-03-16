#ifndef DRAWOBJECT_HPP
#define DRAWOBJECT_HPP

#include "DrawArea.hpp"

namespace algorithms {

/**
 *
 */
class DrawObject
{
public:
    DrawObject(DrawArea& area);

    virtual ~DrawObject() = default;

    virtual void draw() = 0;

    DrawArea& getArea();

    const DrawArea& getArea() const;

private:
    DrawArea& _area;
};

} // namespace algorithms

#endif // DRAWOBJECT_HPP
