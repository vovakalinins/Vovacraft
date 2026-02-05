#pragma once
#include <vector>
#include "world/chunk/chunk.h"
#include "world/world/world.h"

namespace ChunkMesher
{
    std::vector<float> generateMesh(const World &world, const Chunk &chunk);
}