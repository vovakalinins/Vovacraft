#include "world/chunk.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk(glm::vec3 pos) : position(pos)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    setupFlatWorld();
    updateMesh();
}

Chunk::~Chunk()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Chunk::setupFlatWorld()
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                if (y == 0)
                    blocks[x][y][z] = 1;
                else
                    blocks[x][y][z] = 0;
            }
        }
    }
}

bool Chunk::isVoid(int x, int y, int z)
{
    // check neighbour chunks later
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE)
        return true;

    return blocks[x][y][z] == 0;
}

void Chunk::updateMesh()
{
    std::vector<float> vertices;

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z] == 0)
                    continue;

                // FACE CULLING:
                if (isVoid(x + 1, y, z))
                    addFace(vertices, x, y, z, 3); // RIGHT
                if (isVoid(x - 1, y, z))
                    addFace(vertices, x, y, z, 2); // LEFT
                if (isVoid(x, y + 1, z))
                    addFace(vertices, x, y, z, 4); // TOP
                if (isVoid(x, y - 1, z))
                    addFace(vertices, x, y, z, 5); // BOTTOM
                if (isVoid(x, y, z + 1))
                    addFace(vertices, x, y, z, 0); // FRONT
                if (isVoid(x, y, z - 1))
                    addFace(vertices, x, y, z, 1); // BACK
            }
        }
    }

    vertexCount = vertices.size() / 5; // 5 floats per vertex (3 pos + 2 tex)

    // Upload vertices to GPU
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Attribute 0: Position (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Attribute 1: Texture Coords (2 floats)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind to be safe
}

void Chunk::render(unsigned int shaderID)
{
    if (vertexCount == 0)
        return;

    glBindVertexArray(VAO);

    int modelLoc = glGetUniformLocation(shaderID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Chunk::addFace(std::vector<float> &vertices, float x, float y, float z, int faceType)
{
    // 3D Cube Face Definitions
    // Format: x, y, z, u, v
    // We add 'x,y,z' to the vertex position to move the face to the correct block
    float faces[6][30] = {
        // Front (z+1)
        {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
        // Back (z-1)
        {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
        // Left (x-1)
        {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
        // Right (x+1)
        {0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
        // Top (y+1)
        {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
        // Bottom (y-1)
        {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f}};

    for (int i = 0; i < 6; i++)
    {
        vertices.push_back(faces[faceType][i * 5] + x);     // X + blockX
        vertices.push_back(faces[faceType][i * 5 + 1] + y); // Y + blockY
        vertices.push_back(faces[faceType][i * 5 + 2] + z); // Z + blockZ
        vertices.push_back(faces[faceType][i * 5 + 3]);     // U
        vertices.push_back(faces[faceType][i * 5 + 4]);     // V
    }
}