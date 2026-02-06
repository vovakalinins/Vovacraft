#pragma once
#include <vector>
#include <utility>
#include "world/chunk/chunk.h"
#include "world/world/world.h"

struct MeshData {
    std::vector<float> opaqueVerts;
    std::vector<float> transparentVerts;
};

namespace ChunkMesher
{
    MeshData generateMesh(const World &world, const Chunk &chunk);
}
