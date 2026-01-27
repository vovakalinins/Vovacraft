#pragma once
#include <vector>
#include <memory>
#include "world/chunk/chunk.h"

class World {
public:
    std::vector<std::unique_ptr<Chunk>> chunks;

    World() = default;

    void addChunk(std::unique_ptr<Chunk> chunk);
    const Chunk* getChunkAt(int worldX, int worldZ) const;
    uint8_t getBlock(int x, int y, int z) const;
};
