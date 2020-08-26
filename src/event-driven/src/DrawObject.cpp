#include "DrawObject.hpp"

namespace algorithms {

DrawObject::DrawObject(DrawArea& area)
    : _area{area}
{
}

DrawArea&
DrawObject::getArea()
{
    return _area;
}

const DrawArea&
DrawObject::getArea() const
{
    return _area;
}

} // namespace algorithms
