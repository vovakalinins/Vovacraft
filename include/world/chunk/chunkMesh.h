#pragma once
#include <vector>
#include <glm/glm.hpp>

class ChunkMesh
{
public:
    unsigned int VAO, VBO;
    unsigned int vertexCount;

    ChunkMesh();
    ~ChunkMesh();

    void upload(const std::vector<float> &vertices);

    void render(unsigned int shaderID, glm::vec3 position);
};