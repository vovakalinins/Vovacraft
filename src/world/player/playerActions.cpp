#include "world/player/playerActions.h"
#include <world/data/blocks.h>
#include "world/physics/raycast.h"
#include "world/physics/collisions.h"

void PlayerActions::breakBlock(const Player &player, World &world)
{
    auto targettedBlock = getRaycastedBlock(player, world);
    if (targettedBlock.has_value())
    {
        glm::ivec3 targettedPos = targettedBlock.value().hitPos;
        world.setBlock(targettedPos.x, targettedPos.y, targettedPos.z, Blocks::Air);
    }
}

void PlayerActions::placeBlock(const Player &player, World &world)
{
    auto targettedBlock = getRaycastedBlock(player, world);
    if (targettedBlock.has_value())
    {
        glm::ivec3 placePos = targettedBlock.value().placePos;
        if (wouldBlockCollideWithPlayer(player, placePos))
            return;
        world.setBlock(placePos.x, placePos.y, placePos.z, Blocks::Dirt);
    }
}