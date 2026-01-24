#pragma once
#include "world/world/world.h"
#include "PerlinNoise.hpp"

class WorldGenerator {
public:
    static void generateFlatWorld(World& world, int sizeX, int sizeZ);
    static void generateSeededWorld(World& world, int sizeX, int sizeZ, siv::PerlinNoise::seed_type seed);
};