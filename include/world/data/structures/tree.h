#pragma once
#include "world/data/blocks.h"
#include "world/data/structures.h"
#include "world/world/world.h"
#include <cmath>

class Tree : public Structure
{
public:
    void generate(World& world, int worldX, int worldY, int worldZ) override
    {
        int trunkHeight = 6;
        int leafRadius = 3;

        for (int i = 0; i < trunkHeight; i++)
        {
            world.setBlock(worldX, worldY + i, worldZ, Blocks::Log);
        }

        int canopyCenterY = worldY + trunkHeight;

        for (int ly = -leafRadius; ly <= leafRadius; ly++)
        {
            for (int lx = -leafRadius; lx <= leafRadius; lx++)
            {
                for (int lz = -leafRadius; lz <= leafRadius; lz++)
                {
                    float distance = std::sqrt(static_cast<float>(lx * lx + ly * ly + lz * lz));
                    if (distance > leafRadius)
                        continue;
                    int gx = worldX + lx;
                    int gy = canopyCenterY + ly;
                    int gz = worldZ + lz;
                    if (world.getBlock(gx, gy, gz) == Blocks::Air)
                        world.setBlock(gx, gy, gz, Blocks::Leaves);
                }
            }
        }
    }
};