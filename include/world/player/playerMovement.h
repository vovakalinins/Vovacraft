#pragma once
#include "world/player/player.h"
#include "world/world/world.h"

namespace PlayerMovement
{
    const float SPEED = 16.0f;
    const float MOUSE_SENSITIVITY = 0.1f;

    void moveForward(Player &player, float deltaTime);
    void moveBackward(Player &player, float deltaTime);
    void moveLeft(Player &player, float deltaTime);
    void moveRight(Player &player, float deltaTime);
    void flyUp(Player &player, float deltaTime);   // Placeholder for Jump
    void flyDown(Player &player, float deltaTime); // Placeholder for Crouch

    void look(Player &player, float xOffset, float yOffset);

    void update(Player &player, const World &world, float deltaTime);

    bool isOnGround(Player &player, const World &world);
    void applyGravity(Player &player, const World &world, float deltaTime);
}