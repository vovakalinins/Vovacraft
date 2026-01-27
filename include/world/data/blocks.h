#pragma once
#include <cstdint>

enum TextureId : uint8_t {
    TEX_GRASS_TOP = 0,
    TEX_STONE = 1,
    TEX_DIRT = 2,
    TEX_GRASS_SIDE = 3,
    TEX_COBBLESTONE = 16,
    TEX_BEDROCK = 17,
    TEX_WATER_STATIONARY = 223,
    TEX_SAND = 18,
};

enum Blocks : uint8_t
{
    Air = 0,
    Stone = 1,
    Grass = 2,
    Dirt = 3,
    Cobblestone = 4,
    Planks = 5,
    Sapling = 6,
    Bedrock = 7,
    WaterFlowing = 8,
    WaterStationary = 9,
    LavaFlowing = 10,
    LavaStationary = 11,
    Sand = 12,
    Gravel = 13,
    GoldOre = 14,
    IronOre = 15,
    CoalOre = 16,
    Log = 17,
    Leaves = 18,
    Sponge = 19,
    Glass = 20,
    LapisOre = 21,
    LapisBlock = 22,
    Dispenser = 23,
    Sandstone = 24,
    NoteBlock = 25,
    BedBlock = 26,
};

struct BlockData {
    uint8_t texTop;
    uint8_t texBottom;
    uint8_t texSide;
    bool colorTop;
    bool colorSide;
    bool colorBottom;
    float r, g, b;
};

extern BlockData BLOCK_DATABASE[256];

void initBlockDatabase();
