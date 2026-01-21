#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include <vector>
#include "vector2f.h"
#include "rect.h"
#include "circle.h"

namespace algo {
	bool aabbCollisionCheck(Rect& rect1, Rect& rect2);
	bool circleCollisionCheck(Circle& c1, Circle& c2);
}

#endif
