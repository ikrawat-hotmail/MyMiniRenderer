#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <map>
#include "rigidBody2D.h"
#include "vector2f.h"
#include "vector3f.h"
#include "polygon2D.h"
#include "sj.h"

#define FILEPATH "../../resources/"

class ModelLoader {
private:

    const std::string dirPath = FILEPATH;

    ModelLoader() {}

    ModelLoader(const ModelLoader&) = delete;

    ModelLoader& operator=(const ModelLoader&) = delete;

    int parseModelFromJson(
                    std::vector<std::shared_ptr<RigidBody2D>>& rigidBodyArr,
                    std::string jsonStr);

    int loadModels(
        std::vector<std::shared_ptr<RigidBody2D>>& rigidBodyArr,
        std::string path = FILEPATH);

    bool keyEquals(sj_Value key, const char* str);

    float extractNumber(sj_Value val);

    std::string extractString(sj_Value val);

    Vec2f parseVec2f(sj_Reader* reader, sj_Value arrayVal);

    Vec3f parseVec3f(sj_Reader* reader, sj_Value arrayVal);

public:
    static ModelLoader& getInstance() {
        static ModelLoader modelloader;
        return modelloader;
    }

    int init(std::vector<std::shared_ptr<RigidBody2D>>& rigidBodyArr);
};

#endif
