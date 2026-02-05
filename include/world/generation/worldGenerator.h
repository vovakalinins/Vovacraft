#pragma once
#include "world/world/world.h"
#include "PerlinNoise.hpp"

class WorldGenerator {
public:
    glm::ivec3 spawnPoint;
    static void generateFlatWorld(World& world, int sizeX, int sizeZ);
    static void generateSeededWorld(World& world, int sizeX, int sizeZ, siv::PerlinNoise::seed_type seed);
};