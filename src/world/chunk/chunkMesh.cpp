#include "world/chunk/chunkMesh.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

ChunkMesh::ChunkMesh() : vertexCount(0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

ChunkMesh::~ChunkMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void ChunkMesh::upload(const std::vector<float> &vertices)
{
    vertexCount = vertices.size() / 5; // 3 pos + 2 tex

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Texture (Location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void ChunkMesh::render(unsigned int shaderID, glm::vec3 position)
{
    if (vertexCount == 0)
        return;

    glBindVertexArray(VAO);

    // Translate to the chunk's world position
    int modelLoc = glGetUniformLocation(shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}