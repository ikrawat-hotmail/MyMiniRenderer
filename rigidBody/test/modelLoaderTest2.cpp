#include "modelLoader.h"
#include "rigidBody2D.h"
#include "collider2D.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << "=== ModelLoader Test 2: Testing Collider Parsing ===" << std::endl;
    std::cout << std::endl;

    // Use dedicated test resources directory with only sample2.json
    std::string testResourcePath = "../../resources/test/";
    
    std::vector<std::shared_ptr<RigidBody2D>> rigidBodies;
    ModelLoader& loader = ModelLoader::getInstance();
    
    std::cout << "Loading models from: " << testResourcePath << std::endl;
    int result = loader.loadModels(rigidBodies, testResourcePath);
    
    if (result != 0) {
        std::cerr << "ERROR: Failed to load models" << std::endl;
        return 1;
    }

    std::cout << "\n=== Parsing Results ===" << std::endl;
    std::cout << "Total RigidBodies loaded: " << rigidBodies.size() << std::endl;
    std::cout << std::endl;

    // Verify and display results
    for (size_t i = 0; i < rigidBodies.size(); i++) {
        auto& body = rigidBodies[i];
        
        std::cout << "RigidBody #" << (i + 1) << ":" << std::endl;
        std::cout << "  ID: " << body->mId << std::endl;
        std::cout << "  Position: [" << body->mPosition.x << ", " << body->mPosition.y << "]" << std::endl;
        std::cout << "  Orientation: " << body->mOrientation << " radians" << std::endl;
        
        std::cout << "  Geometry Shapes: " << body->mPolygons.size() << std::endl;
        for (size_t j = 0; j < body->mPolygons.size(); j++) {
            auto& shape = body->mPolygons[j];
            std::cout << "    Shape #" << (j + 1) << ": ";
            
            BodyType type = shape->getType();
            if (type == BodyType::CIRCLE) {
                std::cout << "Circle";
            } else if (type == BodyType::RECTANGLE) {
                std::cout << "Rectangle";
            } else {
                std::cout << "Unknown";
            }
            
            std::cout << " at relative position [" 
                      << shape->relativePosition.x << ", " 
                      << shape->relativePosition.y << "]" << std::endl;
        }
        
        std::cout << "  Colliders: " << body->mColliders.size() << std::endl;
        for (size_t j = 0; j < body->mColliders.size(); j++) {
            auto& collider = body->mColliders[j];
            std::cout << "    Collider #" << (j + 1) << ": ";
            
            // Try to cast to specific collider types
            if (auto circleCollider = std::dynamic_pointer_cast<CircleCollider>(collider)) {
                std::cout << "CircleCollider with radius " << circleCollider->getRadius()
                          << " at position [" << circleCollider->getPosition().x 
                          << ", " << circleCollider->getPosition().y << "]" << std::endl;
            } else if (auto rectCollider = std::dynamic_pointer_cast<RectangleCollider>(collider)) {
                std::cout << "RectangleCollider: min[" 
                          << rectCollider->getMin().x << ", " << rectCollider->getMin().y 
                          << "], max[" << rectCollider->getMax().x << ", " << rectCollider->getMax().y << "]" << std::endl;
            } else {
                std::cout << "Unknown collider type" << std::endl;
            }
        }
        
        std::cout << std::endl;
    }

    // Validation checks
    std::cout << "=== Validation ===" << std::endl;
    bool allTestsPassed = true;

    // Test 1: Check we have 2 rigid bodies
    if (rigidBodies.size() != 2) {
        std::cerr << "FAIL: Expected 2 rigid bodies, got " << rigidBodies.size() << std::endl;
        allTestsPassed = false;
    } else {
        std::cout << "PASS: Loaded 2 rigid bodies" << std::endl;
    }

    // Test 2: Check rigidBody1 has correct number of shapes and colliders
    if (rigidBodies.size() >= 1) {
        auto& body1 = rigidBodies[0];
        if (body1->mPolygons.size() != 2) {
            std::cerr << "FAIL: rigidBody1 should have 2 geometry shapes, got " 
                      << body1->mPolygons.size() << std::endl;
            allTestsPassed = false;
        } else {
            std::cout << "PASS: rigidBody1 has 2 geometry shapes" << std::endl;
        }

        if (body1->mColliders.size() != 2) {
            std::cerr << "FAIL: rigidBody1 should have 2 colliders, got " 
                      << body1->mColliders.size() << std::endl;
            allTestsPassed = false;
        } else {
            std::cout << "PASS: rigidBody1 has 2 colliders" << std::endl;
        }
    }

    // Test 3: Check rigidBody2 has correct number of shapes and colliders
    if (rigidBodies.size() >= 2) {
        auto& body2 = rigidBodies[1];
        if (body2->mPolygons.size() != 1) {
            std::cerr << "FAIL: rigidBody2 should have 1 geometry shape, got " 
                      << body2->mPolygons.size() << std::endl;
            allTestsPassed = false;
        } else {
            std::cout << "PASS: rigidBody2 has 1 geometry shape" << std::endl;
        }

        if (body2->mColliders.size() != 2) {
            std::cerr << "FAIL: rigidBody2 should have 2 colliders, got " 
                      << body2->mColliders.size() << std::endl;
            allTestsPassed = false;
        } else {
            std::cout << "PASS: rigidBody2 has 2 colliders" << std::endl;
        }
    }

    std::cout << std::endl;
    if (allTestsPassed) {
        std::cout << "=== ALL TESTS PASSED ===" << std::endl;
        return 0;
    } else {
        std::cout << "=== SOME TESTS FAILED ===" << std::endl;
        return 1;
    }
}
