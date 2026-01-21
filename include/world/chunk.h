#pragma once
#include <vector>
#include <glm/glm.hpp>

const int CHUNK_SIZE = 16;

class Chunk
{
public:
    unsigned char blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    glm::vec3 position;

    unsigned int VAO, VBO;
    unsigned int vertexCount;

    Chunk(glm::vec3 pos);
    ~Chunk();

    void setupFlatWorld();
    void updateMesh();
    void render(unsigned int shaderID);
private:
    void addFace(std::vector<float>& vertices, float x, float y, float z, int faceType);
    bool isVoid(int x, int y, int z);
};