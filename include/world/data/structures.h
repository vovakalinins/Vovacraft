#pragma once
#include "world/data/blocks.h"
#include "world/chunk/chunk.h"

struct structureBlock
{
    int x, y, z;
    Blocks block;
};

class Structure
{
public:
    virtual ~Structure() = default;
    virtual void generate(Chunk &chunk, int x, int y, int z) = 0;
};