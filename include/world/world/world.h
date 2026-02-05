#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "world/chunk/chunk.h"

class World {
public:
    glm::ivec3 worldSpawn;

    std::vector<std::unique_ptr<Chunk>> chunks;

    World() = default;

    void addChunk(std::unique_ptr<Chunk> chunk);
    const Chunk* getChunkAt(int worldX, int worldZ) const;
    Chunk* getChunkAt(int worldX, int worldZ);
    uint8_t getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, uint8_t type);
    void computeSpawn();
};
