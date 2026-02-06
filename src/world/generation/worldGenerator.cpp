#include "world/generation/worldGenerator.h"
#include "PerlinNoise.hpp"
#include "world/generation/chunkGenerator.h"
#include "world/generation/populators/foliageGenerator.h"
#include <iostream>
#include <chrono>

void WorldGenerator::generateFlatWorld(World &world, int sizeX, int sizeZ)
{
    for (int x = 0; x < sizeX; x++)
    {
        for (int z = 0; z < sizeZ; z++)
        {
            glm::ivec2 pos(x * CHUNK_SIZE, z * CHUNK_SIZE);
            auto chunk = std::make_unique<Chunk>(pos);
            ChunkGenerator::makeFlat(*chunk);
            world.addChunk(std::move(chunk));
        }
    }
}

void WorldGenerator::generateSeededWorld(World &world, int sizeX, int sizeZ, siv::PerlinNoise::seed_type seed)
{
    const siv::PerlinNoise perlin{seed};
    const siv::PerlinNoise continental{seed + 1};
    const siv::PerlinNoise foliageNoise{seed + 2};

    for (int x = 0; x < sizeX; x++)
    {
        for (int z = 0; z < sizeZ; z++)
        {
            auto start = std::chrono::high_resolution_clock::now();

            glm::ivec2 pos(x * CHUNK_SIZE, z * CHUNK_SIZE);
            auto chunk = std::make_unique<Chunk>(pos);
            ChunkGenerator::makeSeeded(world, *chunk, perlin, continental);

            world.addChunk(std::move(chunk));

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Generated chunk " << pos.x << ", " << pos.y << " in " << elapsed.count() << "ms" << std::endl;
        }
    }
    for (auto &c : world.chunks)
        generateFoliage(world, *c, foliageNoise);
}
