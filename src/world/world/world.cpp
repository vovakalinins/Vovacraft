#include "world/world/world.h"
#include "world/data/blocks.h"

bool World::isSolidBlock(uint8_t block)
{
    return block != Blocks::Air && block != Blocks::WaterStationary &&
           block != Blocks::WaterFlowing && block != Blocks::LavaFlowing &&
           block != Blocks::LavaStationary;
}

int World::getSurfaceY(const World &world, int worldX, int worldZ)
{
    for (int worldY = Y_MAX; worldY >= Y_MIN; worldY--)
    {
        uint8_t block = world.getBlock(worldX, worldY, worldZ);
        if (!isSolidBlock(block))
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

void World::computeSpawn()
{
    if (chunks.empty())
    {
        worldSpawn = glm::ivec3(0, SEA_LEVEL + 1, 0);
        return;
    }

    int minX = chunks[0]->position.x;
    int maxX = minX + CHUNK_SIZE;
    int minZ = chunks[0]->position.y;
    int maxZ = minZ + CHUNK_SIZE;
    for (size_t i = 1; i < chunks.size(); i++)
    {
        if (chunks[i]->position.x < minX) minX = chunks[i]->position.x;
        if (chunks[i]->position.x + CHUNK_SIZE > maxX) maxX = chunks[i]->position.x + CHUNK_SIZE;
        if (chunks[i]->position.y < minZ) minZ = chunks[i]->position.y;
        if (chunks[i]->position.y + CHUNK_SIZE > maxZ) maxZ = chunks[i]->position.y + CHUNK_SIZE;
    }

    int centerX = (minX + maxX) / 2;
    int centerZ = (minZ + maxZ) / 2;

    int surfaceY = getSurfaceY(*this, centerX, centerZ);
    if (surfaceY >= 0)
    {
        worldSpawn = glm::ivec3(centerX, surfaceY + 1, centerZ);
        return;
    }

    int maxR = ((maxX - minX) > (maxZ - minZ) ? (maxX - minX) : (maxZ - minZ)) / 2 + 1;
    for (int r = 1; r <= maxR; r++)
    {
        for (int i = -r; i <= r; i++)
        {
            int wx = centerX + i;
            int wz = centerZ - r;
            surfaceY = getSurfaceY(*this, wx, wz);
            if (surfaceY >= 0) { worldSpawn = glm::ivec3(wx, surfaceY + 1, wz); return; }

            wz = centerZ + r;
            surfaceY = getSurfaceY(*this, wx, wz);
            if (surfaceY >= 0) { worldSpawn = glm::ivec3(wx, surfaceY + 1, wz); return; }
        }
        for (int i = -r + 1; i < r; i++)
        {
            int wx = centerX - r;
            int wz = centerZ + i;
            surfaceY = getSurfaceY(*this, wx, wz);
            if (surfaceY >= 0) { worldSpawn = glm::ivec3(wx, surfaceY + 1, wz); return; }

            wx = centerX + r;
            surfaceY = getSurfaceY(*this, wx, wz);
            if (surfaceY >= 0) { worldSpawn = glm::ivec3(wx, surfaceY + 1, wz); return; }
        }
    }

    worldSpawn = glm::ivec3(centerX, SEA_LEVEL + 1, centerZ);
}

void World::addChunk(std::unique_ptr<Chunk> chunk)
{
    chunks.push_back(std::move(chunk));
}

const Chunk *World::getChunkAt(int worldX, int worldZ) const
{
    int cx = (worldX >= 0) ? (worldX / CHUNK_SIZE) * CHUNK_SIZE : ((worldX + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;
    int cz = (worldZ >= 0) ? (worldZ / CHUNK_SIZE) * CHUNK_SIZE : ((worldZ + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;

    for (const auto &c : chunks)
    {
        if (c->position.x == cx && c->position.y == cz)
        {
            return c.get();
        }
    }
    return nullptr;
}

Chunk *World::getChunkAt(int worldX, int worldZ)
{
    int cx = (worldX >= 0) ? (worldX / CHUNK_SIZE) * CHUNK_SIZE : ((worldX + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;
    int cz = (worldZ >= 0) ? (worldZ / CHUNK_SIZE) * CHUNK_SIZE : ((worldZ + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;

    for (auto &c : chunks)
    {
        if (c->position.x == cx && c->position.y == cz)
        {
            return c.get();
        }
    }
    return nullptr;
}

uint8_t World::getBlock(int x, int y, int z) const
{
    const Chunk *chunk = getChunkAt(x, z);
    if (!chunk)
        return 0;

    int lx = x - chunk->position.x;
    int lz = z - chunk->position.y;
    return chunk->getBlockWorld(lx, y, lz);
}

void World::setBlock(int x, int y, int z, uint8_t type)
{
    Chunk *chunk = getChunkAt(x, z);
    if (!chunk)
        return;
    int lx = x - chunk->position.x;
    int lz = z - chunk->position.y;
    chunk->setBlockWorld(lx, y, lz, type);
}
