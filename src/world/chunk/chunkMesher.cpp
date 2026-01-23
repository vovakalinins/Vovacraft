#include "world/chunk/chunkMesher.h"

bool isVoid(const Chunk &chunk, int x, int y, int z)
{
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE)
    {
        return true;
    }
    return chunk.blocks[x][y][z] == 0;
}

void addFace(std::vector<float> &vertices, float x, float y, float z, int faceType)
{
    // Face Definitions: x, y, z, u, v
    static const float faces[6][30] = {
        // Front (z+)
        {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
        // Back (z-)
        {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
        // Left (x-)
        {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
        // Right (x+)
        {0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
        // Top (y+)
        {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
        // Bottom (y-)
        {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f}};

    for (int i = 0; i < 6; i++)
    {
        vertices.push_back(faces[faceType][i * 5] + x);
        vertices.push_back(faces[faceType][i * 5 + 1] + y);
        vertices.push_back(faces[faceType][i * 5 + 2] + z);
        vertices.push_back(faces[faceType][i * 5 + 3]);
        vertices.push_back(faces[faceType][i * 5 + 4]);
    }
}

std::vector<float> ChunkMesher::generateMesh(const Chunk &chunk)
{
    std::vector<float> vertices;
    vertices.reserve(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 5);

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (chunk.blocks[x][y][z] == 0)
                    continue;

                // Face Culling Logic
                if (isVoid(chunk, x + 1, y, z))
                    addFace(vertices, x, y, z, 3); // Right
                if (isVoid(chunk, x - 1, y, z))
                    addFace(vertices, x, y, z, 2); // Left
                if (isVoid(chunk, x, y + 1, z))
                    addFace(vertices, x, y, z, 4); // Top
                if (isVoid(chunk, x, y - 1, z))
                    addFace(vertices, x, y, z, 5); // Bottom
                if (isVoid(chunk, x, y, z + 1))
                    addFace(vertices, x, y, z, 0); // Front
                if (isVoid(chunk, x, y, z - 1))
                    addFace(vertices, x, y, z, 1); // Back
            }
        }
    }
    return vertices;
}