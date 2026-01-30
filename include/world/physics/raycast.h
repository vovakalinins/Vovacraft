#include "glm/glm.hpp"
#include "world/world/world.h"
#include "world/player/player.h"
#include "world/data/blocks.h"

struct RaycastResult {
    glm::ivec3 hitPos;
    glm::ivec3 placePos;
    bool didHit = false;
};

std::optional<RaycastResult> getRaycastedBlock(const Player& player, World& world );