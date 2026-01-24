#pragma once
#include "world/player/player.h"
#include "world/world/world.h"

namespace PlayerMovement
{
    const float WALK_SPEED = 43.0f;
    const float SPRINT_SPEED = 56.0f;
    const float SNEAK_SPEED = 13.0f;
    const float JUMP_FORCE = 8.5f;
    const float FLY_SPEED = 10.0f;

    const float MOUSE_SENSITIVITY = 0.1f;

    void moveForward(Player &player, float deltaTime);
    void moveBackward(Player &player, float deltaTime);
    void moveLeft(Player &player, float deltaTime);
    void moveRight(Player &player, float deltaTime);
    void flyUp(Player &player, float deltaTime);
    void flyDown(Player &player, float deltaTime);
    void jump(Player &player, const World &world);
    void sneak(Player &player, const World &world);

    void look(Player &player, float xOffset, float yOffset);

    void update(Player &player, const World &world, float deltaTime);

    bool isOnGround(Player &player, const World &world);
    void applyGravity(Player &player, const World &world, float deltaTime);
}