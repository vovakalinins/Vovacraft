#pragma once
#include "world/player/player.h"
#include "world/world/world.h"

namespace PlayerActions {
    void breakBlock(const Player &player, World& world);
    void placeBlock(const Player &player, World& world);
    void updateBreaking(Player& player, World& world, float deltaTime, bool leftMouseHeld);
}