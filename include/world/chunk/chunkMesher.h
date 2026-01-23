#pragma once
#include <vector>
#include "world/chunk/chunk.h"

namespace ChunkMesher
{
    // Pure function: Takes Data, Returns Geometry
    std::vector<float> generateMesh(const Chunk &chunk);
}