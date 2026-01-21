#include "world/chunk.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Chunk::Chunk(glm::vec3 pos) : position(pos)
{
    setupFlatWorld();
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

void Chunk::render(unsigned int shaderID, unsigned int VAO)
{
    glBindVertexArray(VAO);
    int modelLoc = glGetUniformLocation(shaderID, "model");

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z] != 0)
                {
                    glm::mat4 model = glm::mat4(1.0f);

                    model = glm::translate(model, position + glm::vec3(x, y, z));
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
    }
}