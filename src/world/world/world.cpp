#include "world/world/world.h"
#include "world/data/blocks.h"

static bool isSolidSpawnBlock(uint8_t block) {
    return block != Blocks::Air && block != Blocks::WaterStationary &&
           block != Blocks::WaterFlowing && block != Blocks::LavaFlowing &&
           block != Blocks::LavaStationary;
}

static int getSurfaceY(const World& world, int worldX, int worldZ) {
    for (int worldY = Y_MAX; worldY >= Y_MIN; worldY--) {
        uint8_t block = world.getBlock(worldX, worldY, worldZ);
        if (!isSolidSpawnBlock(block))
            continue;
        if (worldY >= Y_MAX)
            return -1;
        uint8_t above = world.getBlock(worldX, worldY + 1, worldZ);
        if (above != Blocks::Air)
            continue;
        return worldY;
    }
    return -1;
}

void World::computeSpawn() {
    int bestX = 0, bestZ = 0;
    int bestY = SEA_LEVEL + 1;
    int centerX = 0, centerZ = 0;
    int count = 0;
    for (const auto& c : chunks) {
        centerX += c->position.x;
        centerZ += c->position.y;
        count++;
    }
    if (count > 0) {
        centerX = centerX / count + CHUNK_SIZE / 2;
        centerZ = centerZ / count + CHUNK_SIZE / 2;
    }
    int bestDist = -1;
    for (const auto& c : chunks) {
        for (int lx = 0; lx < CHUNK_SIZE; lx++) {
            for (int lz = 0; lz < CHUNK_SIZE; lz++) {
                int wx = c->position.x + lx;
                int wz = c->position.y + lz;
                int surfaceY = getSurfaceY(*this, wx, wz);
                if (surfaceY < 0)
                    continue;
                int dist = (wx - centerX) * (wx - centerX) + (wz - centerZ) * (wz - centerZ);
                if (bestDist < 0 || dist < bestDist) {
                    bestDist = dist;
                    bestX = wx;
                    bestZ = wz;
                    bestY = surfaceY + 1;
                }
            }
        }
    }
    worldSpawn = glm::ivec3(bestX, bestY, bestZ);
}

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
