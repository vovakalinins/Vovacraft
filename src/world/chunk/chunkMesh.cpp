#include "world/chunk/chunkMesh.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

static void setupVAO(unsigned int VAO, unsigned int VBO, const std::vector<float>& vertices) {
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

ChunkMesh::ChunkMesh() : opaqueVertexCount(0), transparentVertexCount(0) {
    glGenVertexArrays(1, &opaqueVAO);
    glGenBuffers(1, &opaqueVBO);
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
}

ChunkMesh::~ChunkMesh() {
    glDeleteVertexArrays(1, &opaqueVAO);
    glDeleteBuffers(1, &opaqueVBO);
    glDeleteVertexArrays(1, &transparentVAO);
    glDeleteBuffers(1, &transparentVBO);
}

void ChunkMesh::upload(const std::vector<float>& opaqueVerts, const std::vector<float>& transparentVerts) {
    opaqueVertexCount = opaqueVerts.size() / 9;
    transparentVertexCount = transparentVerts.size() / 9;

    if (opaqueVertexCount > 0)
        setupVAO(opaqueVAO, opaqueVBO, opaqueVerts);
    if (transparentVertexCount > 0)
        setupVAO(transparentVAO, transparentVBO, transparentVerts);
}

static void renderMesh(unsigned int VAO, unsigned int vertexCount, unsigned int shaderID, glm::vec3 position) {
    if (vertexCount == 0) return;

    glBindVertexArray(VAO);

    int modelLoc = glGetUniformLocation(shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void ChunkMesh::renderOpaque(unsigned int shaderID, glm::vec3 position) {
    renderMesh(opaqueVAO, opaqueVertexCount, shaderID, position);
}

void ChunkMesh::renderTransparent(unsigned int shaderID, glm::vec3 position) {
    renderMesh(transparentVAO, transparentVertexCount, shaderID, position);
}
