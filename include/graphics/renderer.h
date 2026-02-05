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
    ~Renderer();
    void updateMeshes(World& world);
    void render(const Camera& camera, Shader& shader,
        const glm::ivec3& breakTarget, int breakFace, float breakProgress, bool breakValid);

private:
    std::unordered_map<glm::ivec2, std::unique_ptr<ChunkMesh>, ChunkPosHash, ChunkPosEqual> meshCache;
    unsigned int breakOverlayVAO = 0;
    unsigned int breakOverlayVBO = 0;
};
