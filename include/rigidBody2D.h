#ifndef RIGID_BODY_H
#define RIGID_BODY_H

/*
    This rigid body is a container.
    It comprises several Rectangles and Circles relative to a center of mass.
    The rigid bodies will be tied relative to this center of mass.

    Somehow this is called composite body!!!
    Duh!!!

    It was suggested to seprate Collider and Rigid body separately
    Reason will become clear later!!!
*/

#include <vector>
#include <memory>
#include "polygon2D.h"
#include "vector2f.h"
#include "rect.h"
#include "circle.h"
#include "collider2D.h"

class RigidBody2D {
public:
    Vec2f mPosition;                    // global position
    Vec2f mVelocity;                    // global velocity
    std::string mId;
    float mOrientation;

    // TODO:
    // Textures, rotation, mass, gravity, etc
    // other physics

    std::vector<std::shared_ptr<Polygon2D>> mPolygons;
    std::vector<std::shared_ptr<Collider2D>> mColliders;

    RigidBody2D(Polygon2D& poly);
    RigidBody2D() {}

    BodyType getType() const;

private:
    enum BodyType mType;

private:
    
};
#endif
