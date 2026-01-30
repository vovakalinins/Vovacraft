#pragma once
#include <vector>
#include "world/chunk/chunk.h"

namespace ChunkMesher
{
    std::vector<float> generateMesh(const Chunk &chunk);
}