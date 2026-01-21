#include "modelLoader.h"
#include "rigidBody2D.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {
    std::vector<std::shared_ptr<RigidBody2D>> somethingunused;
    cout << somethingunused.size() << endl;
    cout << "=======================================" << endl;
    ModelLoader &modelLoaderInstance = ModelLoader::getInstance();
    // replace init with load models along with path
    // modelLoaderInstance.init(somethingunused);

    // cout << "=======================================" << endl;
    // cout << somethingunused.size() << endl;
    // for (auto& eachBody : somethingunused) {
    //     std::cout << eachBody->mId << endl;
    // }
    return 0;
}
