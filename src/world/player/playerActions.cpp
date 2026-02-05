#include "world/player/playerActions.h"
#include "world/data/blocks.h"
#include "world/physics/raycast.h"
#include "world/physics/collisions.h"
#include "core/GameState.h"

void PlayerActions::breakBlock(const Player &player, World &world)
{
    auto targettedBlock = getRaycastedBlock(player, world);
    if (targettedBlock.has_value())
    {
        glm::ivec3 targettedPos = targettedBlock.value().hitPos;
        world.setBlock(targettedPos.x, targettedPos.y, targettedPos.z, Blocks::Air);
    }
}

void PlayerActions::updateBreaking(Player &player, World &world, float deltaTime, bool leftMouseHeld)
{
    if (state.breakCooldownRemaining > 0.0f)
    {
        state.breakCooldownRemaining -= deltaTime;
        state.breakValid = false;
        return;
    }
    if (!leftMouseHeld)
    {
        state.breakValid = false;
        return;
    }
    auto res = getRaycastedBlock(player, world);
    if (!res.has_value())
    {
        state.breakValid = false;
        return;
    }
    glm::ivec3 hitPos = res->hitPos;
    int face = res->hitFace;
    uint8_t block = world.getBlock(hitPos.x, hitPos.y, hitPos.z);
    if (block == Blocks::Air)
    {
        state.breakValid = false;
        return;
    }
    if (player.gameMode == 1)
    {
        world.setBlock(hitPos.x, hitPos.y, hitPos.z, Blocks::Air);
        state.breakValid = false;
        state.breakCooldownRemaining = 0.08f;
        return;
    }
    float bt = getBreakTime(block);
    if (bt <= 0.0f)
    {
        state.breakValid = false;
        return;
    }
    if (state.breakValid && state.breakTarget == hitPos)
    {
        state.breakProgress += deltaTime / bt;
        if (state.breakProgress >= 1.0f)
        {
            world.setBlock(hitPos.x, hitPos.y, hitPos.z, Blocks::Air);
            state.breakValid = false;
            state.breakCooldownRemaining = 0.12f;
        }
        return;
    }
    state.breakTarget = hitPos;
    state.breakFace = face;
    state.breakProgress = deltaTime / bt;
    state.breakValid = true;
    if (state.breakProgress >= 1.0f)
    {
        world.setBlock(hitPos.x, hitPos.y, hitPos.z, Blocks::Air);
        state.breakValid = false;
        state.breakCooldownRemaining = 0.12f;
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