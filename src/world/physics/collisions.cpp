#include "world/physics/collisions.h"
#include <iostream>

bool checkCollision(const Player &player, const World &world, glm::vec3 offset)
{
    glm::vec3 targetPos = player.position + offset;

    float halfWidth = player.width / 2.0f;
    float playerMinX = targetPos.x - halfWidth;
    float playerMaxX = targetPos.x + halfWidth;
    float playerMinY = targetPos.y;
    float playerMaxY = targetPos.y + player.height;
    float playerMinZ = targetPos.z - halfWidth;
    float playerMaxZ = targetPos.z + halfWidth;

    int minBlockX = static_cast<int>(std::round(playerMinX));
    int maxBlockX = static_cast<int>(std::round(playerMaxX));
    int minBlockY = static_cast<int>(std::floor(playerMinY));
    int maxBlockY = static_cast<int>(std::floor(playerMaxY));
    int minBlockZ = static_cast<int>(std::round(playerMinZ));
    int maxBlockZ = static_cast<int>(std::round(playerMaxZ));

    for (int bx = minBlockX; bx <= maxBlockX; bx++)
    {
        for (int by = minBlockY; by <= maxBlockY; by++)
        {
            for (int bz = minBlockZ; bz <= maxBlockZ; bz++)
            {
                auto chunk = world.getChunk(glm::ivec3(bx, by, bz));
                if (chunk)
                {
                    int lx = bx - chunk->position.x;
                    int ly = by;
                    int lz = bz - chunk->position.z;

                    if (ly >= 0 && ly < CHUNK_SIZE)
                    {
                        if (chunk->getBlock(lx, ly, lz) != 0)
                        {
                            float blockMinX = bx - 0.5f;
                            float blockMaxX = bx + 0.5f;
                            float blockMinY = static_cast<float>(by);
                            float blockMaxY = static_cast<float>(by + 1);
                            float blockMinZ = bz - 0.5f;
                            float blockMaxZ = bz + 0.5f;

                            bool overlapX = playerMaxX > blockMinX && playerMinX < blockMaxX;
                            bool overlapY = playerMaxY > blockMinY && playerMinY < blockMaxY;
                            bool overlapZ = playerMaxZ > blockMinZ && playerMinZ < blockMaxZ;

                            if (overlapX && overlapY && overlapZ)
                            {
                                std::cout << "collisionblock: " << lx << ", " << ly << ", " << lz << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool isOnGround(Player &player, const World &world)
{
    float checkY = player.position.y - 0.01f;

    float halfWidth = player.width / 2.0f;
    float minX = player.position.x - halfWidth;
    float maxX = player.position.x + halfWidth;
    float minZ = player.position.z - halfWidth;
    float maxZ = player.position.z + halfWidth;

    int minBlockX = static_cast<int>(std::round(minX));
    int maxBlockX = static_cast<int>(std::round(maxX));
    int blockY = static_cast<int>(std::floor(checkY));
    int minBlockZ = static_cast<int>(std::round(minZ));
    int maxBlockZ = static_cast<int>(std::round(maxZ));

    for (int bx = minBlockX; bx <= maxBlockX; bx++)
    {
        for (int bz = minBlockZ; bz <= maxBlockZ; bz++)
        {
            auto chunk = world.getChunk(glm::ivec3(bx, blockY, bz));
            if (chunk)
            {
                int lx = bx - chunk->position.x;
                int ly = blockY;
                int lz = bz - chunk->position.z;

                if (ly >= 0 && ly < CHUNK_SIZE)
                {
                    if (chunk->getBlock(lx, ly, lz) != 0)
                    {
                        float blockMinX = bx - 0.5f;
                        float blockMaxX = bx + 0.5f;
                        float blockMinZ = bz - 0.5f;
                        float blockMaxZ = bz + 0.5f;

                        bool overlapX = maxX > blockMinX && minX < blockMaxX;
                        bool overlapZ = maxZ > blockMinZ && minZ < blockMaxZ;

                        if (overlapX && overlapZ)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}