#include "world/chunk/chunkMesh.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

ChunkMesh::ChunkMesh() : vertexCount(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

ChunkMesh::~ChunkMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ChunkMesh::upload(const std::vector<float>& vertices) {
    vertexCount = vertices.size() / 9;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void ChunkMesh::render(unsigned int shaderID, glm::vec3 position) {
    if (vertexCount == 0) return;

    glBindVertexArray(VAO);

    int modelLoc = glGetUniformLocation(shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
