#pragma once
#include "world/world/world.h"

class WorldGenerator {
public:
    static void generateFlatWorld(World& world, int sizeX, int sizeZ);
};