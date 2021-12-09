#pragma once

#include "vector.h"

namespace Collision
{
    struct Point final
    {
        vector<2> Location;
    };

    struct Circle final
    {
        float     Diameter;
        vector<2> Location;
    };

    struct Rectangle final
    {
        vector<2> Length;
        float     Angle;
        vector<2> Location;
    };

    bool Collide(Point     const & LHS, Circle    const & RHS);
    bool Collide(Point     const & LHS, Rectangle const & RHS);
    bool Collide(Circle    const & LHS, Point     const & RHS);
    bool Collide(Circle    const & LHS, Circle    const & RHS);
    bool Collide(Circle    const & LHS, Rectangle const & RHS);
    bool Collide(Rectangle const & LHS, Point     const & RHS);
    bool Collide(Rectangle const & LHS, Circle    const & RHS);
    bool Collide(Rectangle const & LHS, Rectangle const & RHS);
}