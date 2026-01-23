#include "world/chunk/chunk.h"
#include <cstring>

Chunk::Chunk(glm::ivec3 pos) : position(pos)
{
    std::memset(blocks, 0, sizeof(blocks));
}

void Chunk::setBlock(int x, int y, int z, unsigned char type)
{
    // oob check
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
    {
        blocks[x][y][z] = type;
    }
}

unsigned char Chunk::getBlock(int x, int y, int z) const
{
    // oob check
    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
    {
        return blocks[x][y][z];
    }
    return 0;
}