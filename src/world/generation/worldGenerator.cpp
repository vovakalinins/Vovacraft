#include "world/generation/worldGenerator.h"
#include "PerlinNoise.hpp"
#include "world/generation/chunkGenerator.h"
#include <iostream>

void WorldGenerator::generateFlatWorld(World &world, int sizeX, int sizeZ)
{
    for (int x = 0; x < sizeX; x++)
    {
        for (int z = 0; z < sizeZ; z++)
        {
            glm::ivec3 pos(x * CHUNK_SIZE, 0, z * CHUNK_SIZE);
            auto newChunk = std::make_unique<Chunk>(pos);

            ChunkGenerator::makeFlat(*newChunk);

            world.addChunk(std::move(newChunk));

            std::cout << "Generated Chunk at " << pos.x << ", " << pos.z << std::endl;
        }
    }
}

void WorldGenerator::generateSeededWorld(World &world, int sizeX, int sizeZ, siv::PerlinNoise::seed_type seed)
{
    const siv::PerlinNoise perlin{seed};
    for (int x = 0; x < sizeX; x++)
    {
        for (int z = 0; z < sizeZ; z++)
        {
            glm::ivec3 pos(x * CHUNK_SIZE, 0, z * CHUNK_SIZE);
            auto newChunk = std::make_unique<Chunk>(pos);

            ChunkGenerator::makeSeeded(*newChunk, perlin);

            world.addChunk(std::move(newChunk));

            std::cout << "Generated Chunk at " << pos.x << ", " << pos.z << std::endl;
        }
    }
}