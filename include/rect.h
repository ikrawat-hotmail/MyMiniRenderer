#ifndef RECT_H
#define RECT_H
#include <iostream>
#include <vector>
#include "vector2f.h"
#include "polygon2D.h"

class Rect : public Polygon2D {
public:
	float minX, maxX;
	float minY, maxY;

	Rect() {}

	// p1 and p2 are corner points
	Rect(const Vec2f& p1, const Vec2f& p2) {
		minX = std::min(p1.x, p2.x);
		maxX = std::max(p1.x, p2.x);
		minY = std::min(p1.y, p2.y);
		maxY = std::max(p1.y, p2.y);
	}

	std::vector<Vec2f> getCorners() const {
		return {
			{minX, minY}, // a
			{maxX, minY}, // b
			{maxX, maxY}, // c
			{minX, maxY}  // d
		};
	}

	void set(Vec2f p1, Vec2f p2) {
		minX = std::min(p1.x, p2.x);
		maxX = std::max(p1.x, p2.x);
		minY = std::min(p1.y, p2.y);
		maxY = std::max(p1.y, p2.y);
	}

	BodyType getType() const {
        return BodyType::RECTANGLE;
    }
};

#endif
