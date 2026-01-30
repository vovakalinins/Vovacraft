#include "world/data/blocks.h"

BlockData BLOCK_DATABASE[256];

void initBlockDatabase()
{
    for (int i = 0; i < 256; i++)
    {
        BLOCK_DATABASE[i] = {0, 0, 0, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};
    }

    BLOCK_DATABASE[Blocks::Stone] = {TEX_STONE, TEX_STONE, TEX_STONE, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};
    BLOCK_DATABASE[Blocks::Dirt] = {TEX_DIRT, TEX_DIRT, TEX_DIRT, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};
    BLOCK_DATABASE[Blocks::Grass] = {TEX_GRASS_TOP, TEX_DIRT, TEX_GRASS_SIDE, true, false, false, 0.48f, 0.75f, 0.39f, 1.0f, false};
    BLOCK_DATABASE[Blocks::Bedrock] = {TEX_BEDROCK, TEX_BEDROCK, TEX_BEDROCK, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};
    BLOCK_DATABASE[Blocks::Sand] = {TEX_SAND, TEX_SAND, TEX_SAND, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};

    BLOCK_DATABASE[Blocks::WaterStationary] = {TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, false, false, false, 1.0f, 1.0f, 1.0f, 0.7f, true};
    BLOCK_DATABASE[Blocks::WaterFlowing] = {TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, TEX_WATER_STATIONARY, false, false, false, 1.0f, 1.0f, 1.0f, 0.7f, true};

    BLOCK_DATABASE[Blocks::Log] = {TEX_LOG_TOP, TEX_LOG_TOP, TEX_LOG, false, false, false, 1.0f, 1.0f, 1.0f, 1.0f, false};
    BLOCK_DATABASE[Blocks::Leaves] = {TEX_LEAVES, TEX_LEAVES, TEX_LEAVES, true, true, true, 0.0f, 0.4f, 0.0f, 1.0f, true};
}
