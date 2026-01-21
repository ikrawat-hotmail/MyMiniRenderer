#include "rigidBody2D.h"

class Renderer {
    int init(std::vector<std::shared_ptr<RigidBody2D>>& bodies);
    int draw(std::vector<std::shared_ptr<RigidBody2D>>& bodies);
};
