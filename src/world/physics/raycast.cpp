#include "world/physics/raycast.h"
#include <cstddef>

std::optional<RaycastResult> getRaycastedBlock(const Player &player, World &world)
{
    glm::vec3 rayOrigin = player.camera.Position;
    glm::vec3 rayDir = player.camera.Front;

    float maxReach = 5.0f;
    float stepSize = 0.05f;

    glm::ivec3 prevPos = glm::ivec3(std::floor(rayOrigin.x),
                                    std::floor(rayOrigin.y),
                                    std::floor(rayOrigin.z));

    for (float t = 0.1f; t < maxReach; t += stepSize)
    {
        glm::vec3 point = rayOrigin + rayDir * t;

        glm::ivec3 currPos = glm::ivec3(std::floor(point.x),
                                        std::floor(point.y),
                                        std::floor(point.z));

        if (currPos != prevPos)
        {
            unsigned char blockType = world.getBlock(currPos.x, currPos.y, currPos.z);

            if (blockType != Blocks::Air)
            {
                RaycastResult result;
                result.didHit = true;
                result.hitPos = currPos;
                result.placePos = prevPos;
                return result;
            }
        }
        prevPos = currPos;
    }
    return std::nullopt;
}