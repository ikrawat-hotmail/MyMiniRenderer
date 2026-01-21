#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <memory>

int Renderer::init(std::vector<std::shared_ptr<RigidBody2D>>& rigidBodies) {
    for (auto& body : rigidBodies) {
        unsigned int VAO, VBO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Upload vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                        body->vertices.size() * sizeof(float),
                        body->vertices.data(),
                        GL_STATIC_DRAW);

        // Upload index data (if using EBO)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                        body->indices.size() * sizeof(unsigned int),
                        body->indices.data(),
                        GL_STATIC_DRAW);

        // Define vertex attribute layout (position only here)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        // Store VAO handle inside the rigid body for later draw
        body->VAO = VAO;
        body->VBO = VBO;
        body->EBO = EBO;
    }
    return 0;
}

int Renderer::draw(std::vector<std::shared_ptr<RigidBody2D>>& bodies) {
    for (auto& body : bodies) {
        glBindVertexArray(body->VAO);
        glDrawElements(GL_TRIANGLES,
                        body->indices.size(),
                        GL_UNSIGNED_INT,
                        0);
    }
    return 0;
}
