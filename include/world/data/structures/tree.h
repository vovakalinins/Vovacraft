#pragma once
#include "world/data/blocks.h"
#include "world/data/structures.h"
#include <iostream>

class Tree : public Structure
{
public:
    void generate(Chunk &chunk, int x, int y, int z) override
    {
        int trunkHeight = 6;
        int leafRadius = 3;

        for (int i = 0; i < trunkHeight; i++)
        {
            chunk.setBlock(x, y + i, z, Blocks::Log);
        }

        int canopyCenterY = y + trunkHeight;

        for (int ly = -leafRadius; ly <= leafRadius; ly++)
        {
            for (int lx = -leafRadius; lx <= leafRadius; lx++)
            {
                for (int lz = -leafRadius; lz <= leafRadius; lz++)
                {

                    float distance = std::sqrt(lx * lx + ly * ly + lz * lz);

                    if (distance <= leafRadius)
                    {
                        int gx = x + lx;
                        int gy = canopyCenterY + ly;
                        int gz = z + lz;
                        if (chunk.getBlock(gx, gy, gz) == Blocks::Air)
                        {
                            chunk.setBlock(gx, gy, gz, Blocks::Leaves);
                        }
                    }
                }
            }
        }
    }
};