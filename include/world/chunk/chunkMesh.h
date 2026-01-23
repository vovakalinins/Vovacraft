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

    // Sends raw float data to the GPU
    void upload(const std::vector<float> &vertices);

    // Calls glDrawArrays
    void render(unsigned int shaderID, glm::vec3 position);
};