#include "world/physics/collisions.h"
#include <cmath>

bool checkCollision(const Player& player, const World& world, glm::vec3 offset) {
    glm::vec3 target = player.position + offset;
    float hw = player.width / 2.0f;

    int minX = (int)std::floor(target.x - hw);
    int maxX = (int)std::floor(target.x + hw);
    int minY = (int)std::floor(target.y);
    int maxY = (int)std::floor(target.y + player.height);
    int minZ = (int)std::floor(target.z - hw);
    int maxZ = (int)std::floor(target.z + hw);

    for (int bx = minX; bx <= maxX; bx++) {
        for (int by = minY; by <= maxY; by++) {
            for (int bz = minZ; bz <= maxZ; bz++) {
                if (by < Y_MIN || by > Y_MAX) continue;
                uint8_t block = world.getBlock(bx, by, bz);
                if (block != 0 && block != Blocks::WaterStationary && block != Blocks::WaterFlowing) {
                    float bMinX = bx - 0.5f, bMaxX = bx + 0.5f;
                    float bMinY = (float)by, bMaxY = (float)(by + 1);
                    float bMinZ = bz - 0.5f, bMaxZ = bz + 0.5f;

                    if (target.x + hw > bMinX && target.x - hw < bMaxX &&
                        target.y + player.height > bMinY && target.y < bMaxY &&
                        target.z + hw > bMinZ && target.z - hw < bMaxZ) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool isOnGround(Player& player, const World& world) {
    float checkY = player.position.y - 0.01f;
    float hw = player.width / 2.0f;

    int minX = (int)std::floor(player.position.x - hw);
    int maxX = (int)std::floor(player.position.x + hw);
    int by = (int)std::floor(checkY);
    int minZ = (int)std::floor(player.position.z - hw);
    int maxZ = (int)std::floor(player.position.z + hw);

    for (int bx = minX; bx <= maxX; bx++) {
        for (int bz = minZ; bz <= maxZ; bz++) {
            if (by < Y_MIN || by > Y_MAX) continue;
            uint8_t block = world.getBlock(bx, by, bz);
            if (block != 0 && block != Blocks::WaterStationary && block != Blocks::WaterFlowing) {
                float bMinX = bx - 0.5f, bMaxX = bx + 0.5f;
                float bMinZ = bz - 0.5f, bMaxZ = bz + 0.5f;

                if (player.position.x + hw > bMinX && player.position.x - hw < bMaxX &&
                    player.position.z + hw > bMinZ && player.position.z - hw < bMaxZ) {
                    return true;
                }
            }
        }
    }
    return false;
}
