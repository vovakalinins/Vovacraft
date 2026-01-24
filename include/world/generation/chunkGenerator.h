#pragma once
#include "world/chunk/chunk.h"
#include "PerlinNoise.hpp"

namespace ChunkGenerator
{
    void makeFlat(Chunk &chunk);
    void makeSeeded(Chunk &chunk, siv::PerlinNoise perlin);

    // void makeNoise(Chunk& chunk, int seed);
}