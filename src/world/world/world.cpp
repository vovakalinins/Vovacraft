#include "world/world/world.h"

void World::addChunk(std::unique_ptr<Chunk> chunk) {
    chunks.push_back(std::move(chunk));
}

const Chunk* World::getChunkAt(int worldX, int worldZ) const {
    int cx = (worldX >= 0) ? (worldX / CHUNK_SIZE) * CHUNK_SIZE : ((worldX + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;
    int cz = (worldZ >= 0) ? (worldZ / CHUNK_SIZE) * CHUNK_SIZE : ((worldZ + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;

    for (const auto& c : chunks) {
        if (c->position.x == cx && c->position.y == cz) {
            return c.get();
        }
    }
    return nullptr;
}

Chunk* World::getChunkAt(int worldX, int worldZ) {
    int cx = (worldX >= 0) ? (worldX / CHUNK_SIZE) * CHUNK_SIZE : ((worldX + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;
    int cz = (worldZ >= 0) ? (worldZ / CHUNK_SIZE) * CHUNK_SIZE : ((worldZ + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;

    for (auto& c : chunks) {
        if (c->position.x == cx && c->position.y == cz) {
            return c.get();
        }
    }
    return nullptr;
}

uint8_t World::getBlock(int x, int y, int z) const {
    const Chunk* chunk = getChunkAt(x, z);
    if (!chunk) return 0;
    
    int lx = x - chunk->position.x;
    int lz = z - chunk->position.y;
    return chunk->getBlockWorld(lx, y, lz);
}

void World::setBlock(int x, int y, int z, uint8_t type) {
    Chunk* chunk = getChunkAt(x, z);
    if (!chunk) return;
    int lx = x - chunk->position.x;
    int lz = z - chunk->position.y;
    chunk->setBlockWorld(lx, y, lz, type);
}
