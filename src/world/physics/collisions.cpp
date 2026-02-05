#include "world/physics/collisions.h"
#include <cmath>

bool wouldBlockCollideWithPlayer(const Player &player, glm::ivec3 blockPos)
{
    float hw = player.width / 2.0f;
    float pMinX = player.position.x - hw, pMaxX = player.position.x + hw;
    float pMinY = player.position.y, pMaxY = player.position.y + player.height;
    float pMinZ = player.position.z - hw, pMaxZ = player.position.z + hw;

    float bMinX = (float)blockPos.x, bMaxX = (float)(blockPos.x + 1);
    float bMinY = (float)blockPos.y, bMaxY = (float)(blockPos.y + 1);
    float bMinZ = (float)blockPos.z, bMaxZ = (float)(blockPos.z + 1);

    return pMaxX > bMinX && pMinX < bMaxX &&
           pMaxY > bMinY && pMinY < bMaxY &&
           pMaxZ > bMinZ && pMinZ < bMaxZ;
}

bool checkCollision(const Player &player, const World &world, glm::vec3 offset)
{
    glm::vec3 target = player.position + offset;
    float hw = player.width / 2.0f;

    float pMinX = target.x - hw;
    float pMaxX = target.x + hw;
    float pMinY = target.y;
    float pMaxY = target.y + player.height;
    float pMinZ = target.z - hw;
    float pMaxZ = target.z + hw;

    int minX = (int)std::floor(pMinX);
    int maxX = (int)std::floor(pMaxX);
    int minY = (int)std::floor(pMinY);
    int maxY = (int)std::floor(pMaxY);
    int minZ = (int)std::floor(pMinZ);
    int maxZ = (int)std::floor(pMaxZ);

    for (int bx = minX; bx <= maxX; bx++)
    {
        for (int by = minY; by <= maxY; by++)
        {
            for (int bz = minZ; bz <= maxZ; bz++)
            {
                if (by < Y_MIN || by > Y_MAX)
                    continue;
                uint8_t block = world.getBlock(bx, by, bz);
                if (block != 0 && block != Blocks::WaterStationary && block != Blocks::WaterFlowing)
                {
                    float bMinX = (float)bx, bMaxX = (float)(bx + 1);
                    float bMinY = (float)by, bMaxY = (float)(by + 1);
                    float bMinZ = (float)bz, bMaxZ = (float)(bz + 1);

                    if (pMaxX > bMinX && pMinX < bMaxX &&
                        pMaxY > bMinY && pMinY < bMaxY &&
                        pMaxZ > bMinZ && pMinZ < bMaxZ)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

float getGroundY(const Player &player, const World &world)
{
    float hw = player.width / 2.0f;
    int minX = (int)std::floor(player.position.x - hw);
    int maxX = (int)std::floor(player.position.x + hw);
    int minZ = (int)std::floor(player.position.z - hw);
    int maxZ = (int)std::floor(player.position.z + hw);

    int startY = (int)std::floor(player.position.y) - 1;

    for (int by = startY; by >= Y_MIN && by > startY - 10; by--)
    {
        for (int bx = minX; bx <= maxX; bx++)
        {
            for (int bz = minZ; bz <= maxZ; bz++)
            {
                uint8_t block = world.getBlock(bx, by, bz);
                if (block != 0 && block != Blocks::WaterStationary && block != Blocks::WaterFlowing)
                {
                    return (float)(by + 1);
                }
            }
        }
    }
    return (float)(Y_MIN - 100);
}

bool isOnGround(Player &player, const World &world)
{
    float groundY = getGroundY(player, world);
    return std::abs(player.position.y - groundY) < 0.01f;
}
