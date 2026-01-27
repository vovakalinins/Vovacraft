#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>

#include "world/world/world.h"
#include "world/chunk/chunkMesh.h"
#include "graphics/shader.h"
#include "graphics/camera.h"

struct ChunkPosHash {
    size_t operator()(const glm::ivec2& k) const {
        return std::hash<int>()(k.x) ^ (std::hash<int>()(k.y) << 16);
    }
};

struct ChunkPosEqual {
    bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

class Renderer {
public:
    Renderer();
    void updateMeshes(const World& world);
    void render(const Camera& camera, Shader& shader);

private:
    std::unordered_map<glm::ivec2, std::unique_ptr<ChunkMesh>, ChunkPosHash, ChunkPosEqual> meshCache;
};
