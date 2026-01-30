#include "graphics/renderer.h"
#include "world/chunk/chunkMesher.h"
#include <iostream>

Renderer::Renderer() {}

void Renderer::updateMeshes(World& world) {
    for (auto& chunk : world.chunks) {
        glm::ivec2 pos = chunk->position;
        if (chunk->meshDirty || meshCache.find(pos) == meshCache.end()) {
            std::vector<float> vertices = ChunkMesher::generateMesh(*chunk);
            auto mesh = std::make_unique<ChunkMesh>();
            mesh->upload(vertices);
            meshCache[pos] = std::move(mesh);
            chunk->meshDirty = false;
        }
    }
}

void Renderer::render(const Camera& camera, Shader& shader) {
    for (const auto& pair : meshCache) {
        glm::ivec2 pos = pair.first;
        ChunkMesh* mesh = pair.second.get();
        mesh->render(shader.ID, glm::vec3(pos.x, 0, pos.y));
    }
}
