#include "graphics/renderer.h"
#include "world/chunk/chunkMesher.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

static const float FACE_QUADS[6][30] = {
    {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}};

static const float FACE_OFFSET[6][3] = {
    {0.0f, 0.0f, 0.001f}, {0.0f, 0.0f, -0.001f}, {-0.001f, 0.0f, 0.0f}, {0.001f, 0.0f, 0.0f}, {0.0f, 0.001f, 0.0f}, {0.0f, -0.001f, 0.0f}};

Renderer::Renderer()
{
    glGenVertexArrays(1, &breakOverlayVAO);
    glGenBuffers(1, &breakOverlayVBO);
}

Renderer::~Renderer()
{
    if (breakOverlayVAO)
        glDeleteVertexArrays(1, &breakOverlayVAO);
    if (breakOverlayVBO)
        glDeleteBuffers(1, &breakOverlayVBO);
}

void Renderer::updateMeshes(World &world)
{
    for (auto &chunk : world.chunks)
    {
        glm::ivec2 pos = chunk->position;
        if (chunk->meshDirty || meshCache.find(pos) == meshCache.end())
        {
            MeshData meshData = ChunkMesher::generateMesh(world, *chunk);
            auto mesh = std::make_unique<ChunkMesh>();
            mesh->upload(meshData.opaqueVerts, meshData.transparentVerts);
            meshCache[pos] = std::move(mesh);
            chunk->meshDirty = false;
        }
    }
}

void Renderer::render(const Camera &camera, Shader &shader, const glm::ivec3 &breakTarget, int breakFace, float breakProgress, bool breakValid)
{
    for (const auto &pair : meshCache)
    {
        glm::ivec2 pos = pair.first;
        ChunkMesh *mesh = pair.second.get();
        mesh->renderOpaque(shader.ID, glm::vec3(pos.x, 0, pos.y));
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    for (const auto &pair : meshCache)
    {
        glm::ivec2 pos = pair.first;
        ChunkMesh *mesh = pair.second.get();
        mesh->renderTransparent(shader.ID, glm::vec3(pos.x, 0, pos.y));
    }

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    if (!breakValid || breakProgress <= 0.0f || breakProgress >= 1.0f)
        return;

    int stage = static_cast<int>(breakProgress * 10.0f);
    if (stage > 9)
        stage = 9;
    int tex = 240 + stage;
    const float TILE = 1.0f / 16.0f;
    int row = tex / 16, col = tex % 16;
    float uMin = col * TILE, uMax = uMin + TILE;
    float vMin = 1.0f - (row + 1) * TILE, vMax = vMin + TILE;

    float bx = static_cast<float>(breakTarget.x);
    float by = static_cast<float>(breakTarget.y);
    float bz = static_cast<float>(breakTarget.z);

    std::vector<float> verts;
    verts.reserve(6 * 6 * 9);
    for (int face = 0; face < 6; face++)
    {
        float ox = FACE_OFFSET[face][0], oy = FACE_OFFSET[face][1], oz = FACE_OFFSET[face][2];
        const float *f = FACE_QUADS[face];
        for (int i = 0; i < 6; i++)
        {
            verts.push_back(bx + f[i * 5] + ox);
            verts.push_back(by + f[i * 5 + 1] + oy);
            verts.push_back(bz + f[i * 5 + 2] + oz);
            float u = f[i * 5 + 3], v = f[i * 5 + 4];
            verts.push_back(u == 0.0f ? uMin : uMax);
            verts.push_back(v == 0.0f ? vMin : vMax);
            verts.push_back(1.0f);
            verts.push_back(1.0f);
            verts.push_back(1.0f);
            verts.push_back(1.0f);
        }
    }

    glBindVertexArray(breakOverlayVAO);
    glBindBuffer(GL_ARRAY_BUFFER, breakOverlayVBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
