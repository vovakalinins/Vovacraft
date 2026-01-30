#include "world/generation/worldGenerator.h"
#include "PerlinNoise.hpp"
#include "world/generation/chunkGenerator.h"
#include <iostream>

void WorldGenerator::generateFlatWorld(World& world, int sizeX, int sizeZ) {
    for (int x = 0; x < sizeX; x++) {
        for (int z = 0; z < sizeZ; z++) {
            glm::ivec2 pos(x * CHUNK_SIZE, z * CHUNK_SIZE);
            auto chunk = std::make_unique<Chunk>(pos);
            ChunkGenerator::makeFlat(*chunk);
            world.addChunk(std::move(chunk));
        }
    }
}

void WorldGenerator::generateSeededWorld(World& world, int sizeX, int sizeZ, siv::PerlinNoise::seed_type seed) {
    const siv::PerlinNoise perlin{seed};
    const siv::PerlinNoise continental{seed + 1};

    for (int x = 0; x < sizeX; x++) {
        for (int z = 0; z < sizeZ; z++) {
            glm::ivec2 pos(x * CHUNK_SIZE, z * CHUNK_SIZE);
            auto chunk = std::make_unique<Chunk>(pos);
            ChunkGenerator::makeSeeded(*chunk, perlin, continental, seed);
            world.addChunk(std::move(chunk));
            std::cout << "Generated chunk " << pos.x << ", " << pos.y << std::endl;
        }
    }
}
