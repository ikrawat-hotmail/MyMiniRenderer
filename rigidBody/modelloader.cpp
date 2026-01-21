#include "modelLoader.h"
#include "vector3f.h"
#include "circle.h"
#include <cstring>

// Helper function to extract string from sv_value
std::string ModelLoader::extractString(sj_Value val) {
    return std::string(val.start, val.end - val.start);
}

// Helper function to extract double from sj_Value
float ModelLoader::extractNumber(sj_Value val) {
    std::string numStr(val.start, val.end - val.start);
    return std::stof(numStr);
}

// Helper function to compare string keys
bool ModelLoader::keyEquals(sj_Value key, const char* str) {
    size_t len = std::strlen(str);
    if ((size_t)(key.end - key.start) != len)
        return false;
    return strncmp(key.start, str, len) == 0;
}

// Helper function to parse [x, y] array into Vec2f
Vec2f ModelLoader::parseVec2f(sj_Reader* reader, sj_Value arrayVal) {
    Vec2f result(0, 0);
    if (arrayVal.type == SJ_ARRAY) {
        sj_Value elem;
        int idx = 0;
        while (sj_iter_array(reader, arrayVal, &elem)) {
            if (idx == 0) result.x = extractNumber(elem);
            else if (idx == 1) result.y = extractNumber(elem);
            idx++;
        }
    }
    return result;
}

// Helper function to parse [x, y, z] array into a struct or three floats
Vec3f ModelLoader::parseVec3f(sj_Reader* reader, sj_Value arrayVal) {
    Vec3f result(0, 0, 0);
    if (arrayVal.type == SJ_ARRAY) {
        sj_Value elem;
        int idx = 0;
        while (sj_iter_array(reader, arrayVal, &elem)) {
            if (idx == 0) result.x = extractNumber(elem);
            else if (idx == 1) result.y = extractNumber(elem);
            else if (idx == 2) result.z = extractNumber(elem);
            idx++;
        }
    }
    return result;
}


// ToDo: collider mechanism parsing need to be added
int ModelLoader::parseModelFromJson(
                std::vector<std::shared_ptr<RigidBody2D>>& rigidBodyArr,
                std::string jsonStr) {
    // clean me
    // for each hirarchy of objects, there will be a separate file
    std::string jsonData(jsonStr);

    // ig this uses length of string being parsed at a time
    sj_Reader reader = sj_reader(&jsonData[0], jsonData.size());

    // root object
    sj_Value arr = sj_read(&reader);
    if (arr.type != SJ_ARRAY) {
        std::cout << "Error: Expected root object\n";
        std::cout << "Error: Expected root object : SJ_TYPE: " << arr.type << std::endl;
        return 1;
    } else {
        std::cout << "This works\n";
    }

    // Parse object fields
    sj_Value obj;

    // parse object
    while (sj_iter_array(&reader, arr, &obj)) {
        auto rigidBodySp = std::make_shared<RigidBody2D>();


        if (obj.type != SJ_OBJECT) {
            std::cout << "Not object" << std::endl;
        } else {
            std::string id;
            Vec2f position;
            float orientation = 0.0f;
            
            sj_Value shapeKey, shapeVal;
            while (sj_iter_object(&reader, obj, &shapeKey, &shapeVal)) {

                // id
                if (keyEquals(shapeKey, "id")) {
                    id = extractString(shapeVal);
                    std::cout << "id: " << id << std::endl;
                    rigidBodySp->mId = id;

                // position
                } else if (keyEquals(shapeKey, "position")) {
                    if (shapeVal.type == SJ_ARRAY) {
                        sj_Value elem;
                        int idx = 0;
                        while (sj_iter_array(&reader, shapeVal, &elem)) {
                            if (idx == 0) position.x = extractNumber(elem);
                            else if (idx == 1) position.y = extractNumber(elem);
                            idx++;
                        }
                        std::cout << "position: [" << position.x << ", " << position.y << "]" << std::endl;
                        rigidBodySp->mPosition.x = position.x;
                        rigidBodySp->mPosition.y = position.y;
                    }

                // orientation
                } else if (keyEquals(shapeKey, "orientation")) {
                    orientation = extractNumber(shapeVal);
                    std::cout << "orientation: " << orientation << std::endl;
                    rigidBodySp->mOrientation = orientation;

                // shapes array
                } else if (keyEquals(shapeKey, "shapes")) {
                    if (shapeVal.type == SJ_ARRAY) {
                        std::cout << "shapes:" << std::endl;
                        sj_Value shapeObj;
                        std::string shapeType = "";
                        while (sj_iter_array(&reader, shapeVal, &shapeObj)) {
                            if (shapeObj.type == SJ_OBJECT) {
                                // First pass: collect all properties
                                std::string shapeType;
                                std::string role = "geometry";  // default role
                                float radius = 0;
                                Vec2f p1(0, 0), p2(0, 0);
                                Vec2f relativePos(0, 0);
                                Vec3f color(0, 0, 0);
                                
                                sj_Value sKey, sVal;
                                while (sj_iter_object(&reader, shapeObj, &sKey, &sVal)) {
                                    if (keyEquals(sKey, "type")) {
                                        shapeType = extractString(sVal);
                                    }
                                    else if (keyEquals(sKey, "role")) {
                                        role = extractString(sVal);
                                    }
                                    else if (keyEquals(sKey, "radius")) {
                                        radius = extractNumber(sVal);
                                    }
                                    else if (keyEquals(sKey, "points")) {
                                        if (sVal.type == SJ_ARRAY) {
                                            sj_Value pointArray;
                                            int pointIdx = 0;
                                            while (sj_iter_array(&reader, sVal, &pointArray)) {
                                                if (pointIdx == 0) p1 = parseVec2f(&reader, pointArray);
                                                else if (pointIdx == 1) p2 = parseVec2f(&reader, pointArray);
                                                pointIdx++;
                                            }
                                        }
                                    }
                                    else if (keyEquals(sKey, "relative_position")) {
                                        relativePos = parseVec2f(&reader, sVal);
                                    }
                                    else if (keyEquals(sKey, "color")) {
                                        color = parseVec3f(&reader, sVal);
                                    }
                                }
                                
                                // Second pass: create objects based on role
                                std::cout << "  type: " << shapeType << ", role: " << role << std::endl;
                                
                                if (role == "geometry") {
                                    // Create geometry shape
                                    std::shared_ptr<Polygon2D> shape2d;
                                    
                                    if (shapeType == "circle" && radius > 0) {
                                        auto circle = std::make_shared<Circle>();
                                        circle->radius = radius;
                                        circle->relativePosition = relativePos;
                                        circle->color = color;
                                        shape2d = circle;
                                        std::cout << "  Created Circle geometry with radius: " << radius << std::endl;
                                    }
                                    else if (shapeType == "rectangle" && (p1.x != 0 || p1.y != 0 || p2.x != 0 || p2.y != 0)) {
                                        auto rect = std::make_shared<Rect>();
                                        rect->set(p1, p2);
                                        rect->relativePosition = relativePos;
                                        rect->color = color;
                                        shape2d = rect;
                                        std::cout << "  Created Rectangle geometry: P1[" << p1.x << ", " << p1.y << "], P2[" << p2.x << ", " << p2.y << "]" << std::endl;
                                    }
                                    
                                    if (shape2d) {
                                        rigidBodySp->mPolygons.push_back(shape2d);
                                    }
                                }
                                else if (role == "collision") {
                                    // Create collider
                                    std::shared_ptr<Collider2D> collider2d;
                                    
                                    if (shapeType == "circle" && radius > 0) {
                                        collider2d = std::make_shared<CircleCollider>(radius, relativePos);
                                        std::cout << "  Created CircleCollider with radius: " << radius << std::endl;
                                    }
                                    else if (shapeType == "rectangle" && (p1.x != 0 || p1.y != 0 || p2.x != 0 || p2.y != 0)) {
                                        auto rectCollider = std::make_shared<RectangleCollider>();
                                        rectCollider->set(p1, p2);
                                        collider2d = rectCollider;
                                        std::cout << "  Created RectangleCollider: min[" << rectCollider->getMin().x << ", " << rectCollider->getMin().y 
                                                  << "], max[" << rectCollider->getMax().x << ", " << rectCollider->getMax().y << "]" << std::endl;
                                    }
                                    
                                    if (collider2d) {
                                        rigidBodySp->mColliders.push_back(collider2d);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            rigidBodyArr.push_back(rigidBodySp);
            std::cout << "---" << std::endl;
            // TODO: Create RigidBody2D with parsed data
            // Note: RigidBody2D requires a Polygon2D in constructor
            // rigidBodeyArr.push_back(body);
        }
    }
    return 0;
}

int ModelLoader::loadModels(std::vector<std::shared_ptr<RigidBody2D>>& rigidBodyArr,
                std::string dirPath) {
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath)) {
        std::cout << "Invalid path or not a directory: " + dirPath << std::endl;
        return -1;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            std::ifstream file(entry.path());
            if (!file) {
                std::cout << "Could not open file: " << entry.path() << std::endl;
                continue;
            }
            std::ostringstream buffer;
            buffer << file.rdbuf();

            parseModelFromJson(rigidBodyArr, buffer.str());
        }
    }
    return 0; 
}
