#pragma once
#include <vector>
#include <glm/glm.hpp>

class ChunkMesh
{
public:
    unsigned int opaqueVAO, opaqueVBO;
    unsigned int opaqueVertexCount;

    unsigned int transparentVAO, transparentVBO;
    unsigned int transparentVertexCount;

    ChunkMesh();
    ~ChunkMesh();

    void upload(const std::vector<float> &opaqueVerts, const std::vector<float> &transparentVerts);

    void renderOpaque(unsigned int shaderID, glm::vec3 position);
    void renderTransparent(unsigned int shaderID, glm::vec3 position);
};
