#include "world/world/world.h"

void World::addChunk(std::unique_ptr<Chunk> chunk)
{
    chunks.push_back(std::move(chunk));
}

const Chunk *World::getChunk(glm::ivec3 pos) const
{
    int cx = (pos.x >= 0) ? (pos.x / CHUNK_SIZE) * CHUNK_SIZE : ((pos.x + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;
    int cz = (pos.z >= 0) ? (pos.z / CHUNK_SIZE) * CHUNK_SIZE : ((pos.z + 1) / CHUNK_SIZE - 1) * CHUNK_SIZE;

    for (const auto &c : chunks)
    {
        if (c->position.x == cx && c->position.z == cz)
        {
            return c.get();
        }
    }
    return nullptr;
}