#pragma once
#include "world/data/blocks.h"

class Chunk;
class World;

struct structureBlock
{
    int x, y, z;
    Blocks block;
};

class Structure
{
public:
    virtual ~Structure() = default;
    virtual void generate(World& world, int worldX, int worldY, int worldZ) = 0;
};