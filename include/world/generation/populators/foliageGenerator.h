#pragma once
#include "PerlinNoise.hpp"
#include "world/chunk/chunk.h"
#include "world/world/world.h"

const int TREE_SPACING = 5;

void generateFoliage(World& world, Chunk& chunk, const siv::PerlinNoise& foliageNoise);
