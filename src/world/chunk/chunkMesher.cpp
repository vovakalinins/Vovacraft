#include "world/chunk/chunkMesher.h"
#include "world/data/blocks.h"

static const float faces[6][30] = {
    {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
     0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
    {0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
     -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
    {0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
    {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
     0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.5f, 1.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f}};

inline bool isVoid(const Chunk &chunk, int x, int y, int z)
{
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE)
        return true;
    return chunk.getBlock(x, y, z) == 0;
}

inline void addFace(std::vector<float> &verts, float x, float y, float z, int face, int tex, float r, float g, float b)
{
    const float TILE = 1.0f / 16.0f;
    int row = tex / 16, col = tex % 16;
    float uMin = col * TILE, uMax = uMin + TILE;
    float vMin = 1.0f - (row + 1) * TILE, vMax = vMin + TILE;

    for (int i = 0; i < 6; i++)
    {
        verts.push_back(faces[face][i * 5] + x);
        verts.push_back(faces[face][i * 5 + 1] + y);
        verts.push_back(faces[face][i * 5 + 2] + z);
        float u = faces[face][i * 5 + 3], v = faces[face][i * 5 + 4];
        verts.push_back(u == 0.0f ? uMin : uMax);
        verts.push_back(v == 0.0f ? vMin : vMax);
        verts.push_back(r);
        verts.push_back(g);
        verts.push_back(b);
    }
}

inline void getVisuals(uint8_t block, int face, int &tex, float &r, float &g, float &b)
{
    BlockData &d = BLOCK_DATABASE[block];
    r = g = b = 1.0f;
    if (face == 4)
    {
        tex = d.texTop;
        if (d.colorTop)
        {
            r = d.r;
            g = d.g;
            b = d.b;
        }
    }
    else if (face == 5)
    {
        tex = d.texBottom;
        if (d.colorBottom)
        {
            r = d.r;
            g = d.g;
            b = d.b;
        }
    }
    else
    {
        tex = d.texSide;
        if (d.colorSide)
        {
            r = d.r;
            g = d.g;
            b = d.b;
        }
    }
}

std::vector<float> ChunkMesher::generateMesh(const Chunk &chunk)
{
    std::vector<float> verts;
    verts.reserve(100000);

    for (int y = 0; y < CHUNK_HEIGHT; y++)
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                uint8_t block = chunk.getBlock(x, y, z);
                if (block == 0)
                    continue;

                float worldY = (float)(y + Y_MIN);
                int tex;
                float r, g, b;

                if (isVoid(chunk, x + 1, y, z))
                {
                    getVisuals(block, 3, tex, r, g, b);
                    addFace(verts, x, worldY, z, 3, tex, r, g, b);
                }
                if (isVoid(chunk, x - 1, y, z))
                {
                    getVisuals(block, 2, tex, r, g, b);
                    addFace(verts, x, worldY, z, 2, tex, r, g, b);
                }
                if (isVoid(chunk, x, y + 1, z))
                {
                    getVisuals(block, 4, tex, r, g, b);
                    addFace(verts, x, worldY, z, 4, tex, r, g, b);
                }
                if (isVoid(chunk, x, y - 1, z))
                {
                    getVisuals(block, 5, tex, r, g, b);
                    addFace(verts, x, worldY, z, 5, tex, r, g, b);
                }
                if (isVoid(chunk, x, y, z + 1))
                {
                    getVisuals(block, 0, tex, r, g, b);
                    addFace(verts, x, worldY, z, 0, tex, r, g, b);
                }
                if (isVoid(chunk, x, y, z - 1))
                {
                    getVisuals(block, 1, tex, r, g, b);
                    addFace(verts, x, worldY, z, 1, tex, r, g, b);
                }
            }
        }
    }
    return verts;
}
