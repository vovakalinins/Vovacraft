#include "world/generation/chunkGenerator.h"
#include "world/chunk/chunk.h"
#include "world/data/blocks.h"
#include <cmath>
#include "world/data/structures.h"
#include "world/data/structures/tree.h"
#include <random>

void ChunkGenerator::makeFlat(Chunk &chunk)
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            for (int y = 0; y < CHUNK_HEIGHT; y++)
            {
                int worldY = y + Y_MIN;
                if (worldY == Y_MIN)
                    chunk.setBlock(x, y, z, Blocks::Bedrock);
                else if (worldY < 60)
                    chunk.setBlock(x, y, z, Blocks::Stone);
                else if (worldY < 63)
                    chunk.setBlock(x, y, z, Blocks::Dirt);
                else if (worldY == 63)
                    chunk.setBlock(x, y, z, Blocks::Grass);
            }
        }
    }
}

void ChunkGenerator::makeSeeded(Chunk &chunk, siv::PerlinNoise perlin, siv::PerlinNoise continental, siv::PerlinNoise::seed_type seed)
{
    int surfaceY[CHUNK_SIZE][CHUNK_SIZE];
    for (int x = 0; x < CHUNK_SIZE; x++)
        for (int z = 0; z < CHUNK_SIZE; z++)
            surfaceY[x][z] = -1;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            double wx = (double)(chunk.position.x + x);
            double wz = (double)(chunk.position.y + z);

            double cont = continental.octave2D_01(wx * 0.002, wz * 0.002, 4);
            double erosion = perlin.octave2D_01(wx * 0.004, wz * 0.004, 4);
            double detail = perlin.octave2D_01(wx * 0.02, wz * 0.02, 6);

            double base;
            if (cont < 0.35)
            {
                base = 30 + cont * 80;
            }
            else if (cont < 0.65)
            {
                double t = (cont - 0.35) / 0.3;
                base = 58 + t * 12 + (erosion - 0.5) * 8;
            }
            else
            {
                double t = (cont - 0.65) / 0.35;
                double mountainHeight = 70 + t * 80 * erosion;
                base = mountainHeight;
            }

            base += (detail - 0.5) * 6;
            int height = (int)base;
            if (height < 1)
                height = 1;
            if (height > Y_MAX - 1)
                height = Y_MAX - 1;

            for (int y = 0; y < CHUNK_HEIGHT; y++)
            {
                int worldY = y + Y_MIN;

                if (worldY < Y_MIN + 5)
                {
                    if (worldY == Y_MIN || (perlin.noise2D_01(wx * 0.5, wz * 0.5 + worldY) < 0.3 + (worldY - Y_MIN) * 0.15))
                        chunk.setBlock(x, y, z, Blocks::Bedrock);
                    else
                        chunk.setBlock(x, y, z, Blocks::Stone);
                }
                else if (worldY < height - 4)
                {
                    chunk.setBlock(x, y, z, Blocks::Stone);
                }
                else if (worldY < height)
                {
                    if (height <= SEA_LEVEL + 2 && height >= SEA_LEVEL - 3)
                        chunk.setBlock(x, y, z, Blocks::Sand);
                    else
                        chunk.setBlock(x, y, z, Blocks::Dirt);
                }
                else if (worldY == height)
                {
                    if (height < SEA_LEVEL - 1)
                        chunk.setBlock(x, y, z, Blocks::Sand);
                    else if (height <= SEA_LEVEL + 2)
                        chunk.setBlock(x, y, z, Blocks::Sand);
                    else
                        chunk.setBlock(x, y, z, Blocks::Grass);
                    surfaceY[x][z] = y;
                }
                else if (worldY <= SEA_LEVEL)
                {
                    chunk.setBlock(x, y, z, Blocks::WaterStationary);
                }
            }
        }
    }

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int localY = surfaceY[x][z];
            if (localY < 0)
                continue;
            if (chunk.getBlock(x, localY, z) != Blocks::Grass)
                continue;
            int worldX = chunk.position.x + x;
            int worldZ = chunk.position.y + z;
            std::mt19937 gen(static_cast<std::mt19937::result_type>(seed ^ (static_cast<uint64_t>(worldX) * 73856093u) ^ (static_cast<uint64_t>(worldZ) * 19349663u)));
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            if (dist(gen) >= 0.025)
                continue;
            std::unique_ptr<Structure> sPtr = std::make_unique<Tree>();
            sPtr->generate(chunk, x, localY, z);
        }
    }
}
