#include "world/generation/chunkGenerator.h"

void ChunkGenerator::makeFlat(Chunk &chunk)
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                if (y == 0)
                {
                    chunk.setBlock(x, y, z, 1);
                }
                else
                {
                    chunk.setBlock(x, y, z, 0);
                }
            }
        }
    }
}