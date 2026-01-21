// Collider class holds the bounding boxes around the geometry
// They appear to be similar to geometry
// but serve a different purpose
#ifndef COLLIDER_H
#define COLLIDER_H
#include "vector2f.h"

enum ColliderType {
    CIRCLE_COLLIDER,
    RECTANGLE_COLLIDER,
    UNDEFINED_COLLIDER
};

class Collider2D {
public:
    virtual ~Collider2D() = default;
    virtual ColliderType getType() const { return ColliderType::UNDEFINED_COLLIDER; }
};

// Circle collider
class CircleCollider : public Collider2D {
public:
    float radius;
    Vec2f position;
    
    CircleCollider(float radius) : radius(radius) {}
    CircleCollider(float radius, Vec2f position) : radius(radius), position(position) {}
    CircleCollider() {}
    
    ColliderType getType() const override { return ColliderType::CIRCLE_COLLIDER; }
    
    void setParams(float radius) { this->radius = radius; }
    void setParams(Vec2f position) { this->position = position; }
    void setParams(float radius, Vec2f position) { this->position = position; }
    Vec2f getPosition() const { return position; }
    float getRadius() const { return radius; }
};

class RectangleCollider : public Collider2D {
public:
    // Min and max points defining the rectangle (like Rect)
    Vec2f min;  // Bottom-left corner
    Vec2f max;  // Top-right corner
    
    RectangleCollider() {}
    RectangleCollider(Vec2f min, Vec2f max) : min(min), max(max) {}
    
    ColliderType getType() const override { return ColliderType::RECTANGLE_COLLIDER; }
    
    void set(Vec2f p1, Vec2f p2) {
        min.x = (p1.x < p2.x) ? p1.x : p2.x;
        min.y = (p1.y < p2.y) ? p1.y : p2.y;
        max.x = (p1.x > p2.x) ? p1.x : p2.x;
        max.y = (p1.y > p2.y) ? p1.y : p2.y;
    }
    
    Vec2f getMin() const { return min; }
    Vec2f getMax() const { return max; }
    Vec2f getCenter() const { return Vec2f((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f); }
};

#endif
