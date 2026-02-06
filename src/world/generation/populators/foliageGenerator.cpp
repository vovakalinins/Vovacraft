#include "world/generation/populators/foliageGenerator.h"
#include "world/chunk/chunk.h"
#include "world/data/blocks.h"
#include "world/data/structures.h"
#include "world/data/structures/tree.h"
#include "world/world/world.h"

void generateFoliage(World &world, Chunk &chunk, const siv::PerlinNoise &foliageNoise)
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int wx = chunk.position.x + x;
            int wz = chunk.position.y + z;
            if (wx % TREE_SPACING != 0 || wz % TREE_SPACING != 0)
                continue;

            int surfaceWorldY = World::getSurfaceY(world, wx, wz);
            if (surfaceWorldY < 0 || surfaceWorldY >= Y_MAX - 1)
                continue;
            if (world.getBlock(wx, surfaceWorldY, wz) != Blocks::Grass)
                continue;

            double n = foliageNoise.octave2D_01(static_cast<double>(wx) * 0.04, static_cast<double>(wz) * 0.04, 3);
            if (n < 0.68)
                continue;

            std::unique_ptr<Structure> sPtr = std::make_unique<Tree>();
            sPtr->generate(world, wx, surfaceWorldY+1, wz);
        }
    }
}
