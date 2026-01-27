#pragma once
#include "glm/glm.hpp"
#include <vector>

const int CHUNK_SIZE = 16;
const int CHUNK_HEIGHT = 320;
const int Y_MIN = -64;
const int Y_MAX = 255;
const int SEA_LEVEL = 62;

class Chunk {
public:
    std::vector<uint8_t> blocks;
    glm::ivec2 position;

    Chunk(glm::ivec2 pos);

    inline int index(int x, int y, int z) const {
        return x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
    }

    void setBlock(int x, int y, int z, uint8_t type);
    uint8_t getBlock(int x, int y, int z) const;
    uint8_t getBlockWorld(int x, int worldY, int z) const;
    void setBlockWorld(int x, int worldY, int z, uint8_t type);
};
