#ifndef POLYGON2D_H
#define POLYGON2D_H

#include "vector2f.h"
#include "vector3f.h"
#include <vector>

enum BodyType {
    CIRCLE,
    RECTANGLE,
    UNDEFINED
};

class Polygon2D {
public:
    Vec2f relativePosition;
    Vec3f color;
    BodyType type;

    Polygon2D() {};
    
    virtual BodyType getType() {
        return BodyType::UNDEFINED;
    }

    virtual ~Polygon2D() {}
};

#endif
