#include "graphics/renderer.h"
#include "world/chunk/chunkMesher.h"
#include <iostream>

Renderer::Renderer() {
}

void Renderer::updateMeshes(const World& world) {
    for (const auto& chunkPtr : world.chunks) {
        glm::ivec3 pos = chunkPtr->position;

        if (meshCache.find(pos) == meshCache.end()) {
            
            std::vector<float> vertices = ChunkMesher::generateMesh(*chunkPtr);
            
            auto mesh = std::make_unique<ChunkMesh>();
            mesh->upload(vertices);

            meshCache[pos] = std::move(mesh);
            std::cout << "Meshed Chunk at " << pos.x << ", " << pos.z << std::endl;
        }
    }
}

void Renderer::render(const Camera& camera, Shader& shader) {

    for (const auto& pair : meshCache) {
        glm::ivec3 pos = pair.first;
        ChunkMesh* mesh = pair.second.get();

        //to do: add frustrum culls
        mesh->render(shader.ID, glm::vec3(pos));
    }
}