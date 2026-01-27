#include "world/data/blocks.h"

BlockData BLOCK_DATABASE[256];

void initBlockDatabase()
{
    for (int i = 0; i < 256; i++)
    {
        BLOCK_DATABASE[i] = {0, 0, 0, false, false, false, 1.0f, 1.0f, 1.0f};
    }

    // Stone
    BLOCK_DATABASE[Blocks::Stone] = {TEX_STONE, TEX_STONE, TEX_STONE, false, false, false, 1.0f, 1.0f, 1.0f};

    // Dirt
    BLOCK_DATABASE[Blocks::Dirt] = {TEX_DIRT, TEX_DIRT, TEX_DIRT, false, false, false, 1.0f, 1.0f, 1.0f};

    // Grass
    BLOCK_DATABASE[Blocks::Grass] = {TEX_GRASS_TOP, TEX_DIRT, TEX_GRASS_SIDE, true, false, false, 0.48f, 0.75f, 0.39f};

    // Bedrock
    BLOCK_DATABASE[Blocks::Bedrock] = {TEX_BEDROCK, TEX_BEDROCK, TEX_BEDROCK, false, false, false, 1.0f, 1.0f, 1.0f};

    // Water
    BLOCK_DATABASE[Blocks::WaterStationary] = {TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, false, false, false, 1.0f, 1.0f, 1.0f};
    BLOCK_DATABASE[Blocks::WaterFlowing] = {TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, false, false, false, 1.0f, 1.0f, 1.0f};

    // Sand
    BLOCK_DATABASE[Blocks::Sand] = {TEX_SAND, TEX_SAND, TEX_SAND, false, false, false, 1.0f, 1.0f, 1.0f};
}
