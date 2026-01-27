#include "world/chunk/chunk.h"

Chunk::Chunk(glm::ivec2 pos) : position(pos), blocks(CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT, 0) {}

void Chunk::setBlock(int x, int y, int z, uint8_t type) {
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_SIZE) {
        blocks[index(x, y, z)] = type;
    }
}

uint8_t Chunk::getBlock(int x, int y, int z) const {
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_SIZE) {
        return blocks[index(x, y, z)];
    }
    return 0;
}

uint8_t Chunk::getBlockWorld(int x, int worldY, int z) const {
    return getBlock(x, worldY - Y_MIN, z);
}

void Chunk::setBlockWorld(int x, int worldY, int z, uint8_t type) {
    setBlock(x, worldY - Y_MIN, z, type);
}
