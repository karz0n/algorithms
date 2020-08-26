#pragma once

#include "DrawArea.hpp"

namespace algorithms {

class DrawObject {
public:
    explicit DrawObject(DrawArea& area);

    virtual ~DrawObject() = default;

    virtual void
    draw()
        = 0;

    DrawArea&
    getArea();

    [[nodiscard]] const DrawArea&
    getArea() const;

private:
    DrawArea& _area;
};

} // namespace algorithms
