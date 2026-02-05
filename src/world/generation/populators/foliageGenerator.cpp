#include "world/generation/populators/foliageGenerator.h"
#include "world/chunk/chunk.h"
#include "world/data/blocks.h"
#include "world/data/structures.h"
#include "world/data/structures/tree.h"

static bool isSolidSurface(uint8_t block)
{
    return block != Blocks::Air && block != Blocks::WaterStationary &&
           block != Blocks::WaterFlowing && block != Blocks::LavaFlowing &&
           block != Blocks::LavaStationary;
}

static int getSurfaceWorldY(const World& world, int wx, int wz)
{
    for (int wy = Y_MAX; wy >= Y_MIN; wy--)
    {
        uint8_t block = world.getBlock(wx, wy, wz);
        if (!isSolidSurface(block))
            continue;
        if (wy >= Y_MAX)
            return -1;
        if (world.getBlock(wx, wy + 1, wz) != Blocks::Air)
            continue;
        return wy;
    }
    return -1;
}

void generateFoliage(World& world, Chunk& chunk, const siv::PerlinNoise& foliageNoise)
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int wx = chunk.position.x + x;
            int wz = chunk.position.y + z;
            if (wx % TREE_SPACING != 0 || wz % TREE_SPACING != 0)
                continue;

            int surfaceWorldY = getSurfaceWorldY(world, wx, wz);
            if (surfaceWorldY < 0 || surfaceWorldY >= Y_MAX - 1)
                continue;
            if (world.getBlock(wx, surfaceWorldY, wz) != Blocks::Grass)
                continue;

            double n = foliageNoise.octave2D_01(static_cast<double>(wx) * 0.04, static_cast<double>(wz) * 0.04, 3);
            if (n < 0.68)
                continue;

            std::unique_ptr<Structure> sPtr = std::make_unique<Tree>();
            sPtr->generate(world, wx, surfaceWorldY, wz);
        }
    }
}
