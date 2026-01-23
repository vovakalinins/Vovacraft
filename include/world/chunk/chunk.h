#pragma once
#include "glm/glm.hpp"

// 16x16 blocks
const int CHUNK_SIZE = 16;

class Chunk {
    public:
    unsigned char blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    glm::ivec3 position;

    Chunk(glm::ivec3 pos);

    void setBlock(int x, int y, int z, unsigned char type);
    unsigned char getBlock(int x, int y, int z) const;
};