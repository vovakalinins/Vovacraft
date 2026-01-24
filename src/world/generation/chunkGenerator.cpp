#include "world/generation/chunkGenerator.h"
#include "world/chunk/chunk.h"
#include "world/data/blocks.h"

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
                    chunk.setBlock(x, y, z, Blocks::Dirt);
                }
                else
                {
                    chunk.setBlock(x, y, z, Blocks::Air);
                }
            }
        }
    }
}

void ChunkGenerator::makeSeeded(Chunk &chunk, siv::PerlinNoise perlin)
{
    const double frequency = 8.0;
    const int octaves = 8;
    const int maxHeight = 12;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            double worldX = (double)(chunk.position.x + x);
            double worldZ = (double)(chunk.position.z + z);

            double noiseVal = perlin.octave2D_01(worldX * frequency, worldZ * frequency, octaves);

            int height = (int)(noiseVal * maxHeight);
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                if (y < height)
                {
                    chunk.setBlock(x, y, z, Blocks::Dirt);
                }
                else if (y == height)
                {
                    chunk.setBlock(x, y, z, Blocks::Dirt); 
                }
                else
                {
                    chunk.setBlock(x, y, z, Blocks::Air);
                }
            }
        }
    }
}