#include <iostream>
#include "modelLoader.h"
#include "collision.h"
#include "rect.h"
#include "vector2f.h"

int main() {
    ModelLoader& modelLoader = ModelLoader::getInstance();
    std::vector<RigidBody2D> rigidBodiesVec;

    // load all the rigid bodies for this scene.
    //modelLoader.init(rigidBodiesVec);

    // currently the models loaded are in recs or circles.
    // for each object convert the model into traingles
    // generate the VAO
    // load these VAO in open GL
    // let openGL do the rendering stuff

    // process rigid bodies.
    for (auto& object : rigidBodiesVec) {
    }

    return 0;
}
