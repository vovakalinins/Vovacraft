#pragma once
#include <vector>
#include <glm/glm.hpp>

const int CHUNK_SIZE = 16;

class Chunk {
    public:
    unsigned char blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    glm::vec3 position;

    Chunk(glm::vec3 pos);
    void setupFlatWorld();
    void render(unsigned int shaderID, unsigned int VAO);
};