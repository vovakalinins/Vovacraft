#pragma once
#include "world/chunk/chunk.h"
#include "world/world/world.h"
#include "PerlinNoise.hpp"

namespace ChunkGenerator
{
    void makeFlat(Chunk &chunk);
    void makeSeeded(World &world, Chunk &chunk, siv::PerlinNoise perlin, siv::PerlinNoise continental);
}