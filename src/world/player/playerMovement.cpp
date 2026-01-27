#include "world/player/playerMovement.h"
#include <glm/glm.hpp>
#include <cmath>
#include "world/physics/gravity.h"
#include "world/player/player.h"
#include "world/chunk/chunk.h"
#include <iostream>
#include "world/physics/collisions.h"

glm::vec3 getBodyForward(const Player &player)
{
    glm::vec3 front;
    front.x = cos(glm::radians(player.yaw));
    front.y = 0.0f;
    front.z = sin(glm::radians(player.yaw));
    return glm::normalize(front);
}

glm::vec3 getBodyRight(const Player &player)
{
    glm::vec3 forward = getBodyForward(player);
    return glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
}

void PlayerMovement::moveForward(Player &player, float deltaTime)
{
    // add sprint
    float currentSpeed = PlayerMovement::WALK_SPEED;

    player.velocity += getBodyForward(player) * currentSpeed * deltaTime;
}

void PlayerMovement::moveBackward(Player &player, float deltaTime)
{
    player.velocity -= getBodyForward(player) * PlayerMovement::WALK_SPEED * deltaTime;
}

void PlayerMovement::moveLeft(Player &player, float deltaTime)
{
    player.velocity -= getBodyRight(player) * PlayerMovement::WALK_SPEED * deltaTime;
}

void PlayerMovement::moveRight(Player &player, float deltaTime)
{
    player.velocity += getBodyRight(player) * PlayerMovement::WALK_SPEED * deltaTime;
}

void PlayerMovement::flyUp(Player &player, float deltaTime)
{
    player.velocity.y += PlayerMovement::FLY_SPEED * deltaTime;
}

void PlayerMovement::jump(Player &player, const World &world)
{
    if (isOnGround(player, world) && std::abs(player.velocity.y) < 0.01f)
    {
        player.velocity.y = JUMP_FORCE;
    }
}

void PlayerMovement::sneak(Player &player, const World &world)
{
    if (isOnGround(player, world))
    {
        player.velocity.y = JUMP_FORCE;
    }
}

void PlayerMovement::flyDown(Player &player, float deltaTime)
{
    player.velocity.y -= PlayerMovement::FLY_SPEED * deltaTime;
}

void PlayerMovement::look(Player &player, float xOffset, float yOffset)
{
    player.yaw += xOffset * MOUSE_SENSITIVITY;

    player.pitch += yOffset * MOUSE_SENSITIVITY;

    if (player.pitch > 89.0f)
        player.pitch = 89.0f;
    if (player.pitch < -89.0f)
        player.pitch = -89.0f;
}

void PlayerMovement::applyGravity(Player &player, const World &world, float deltaTime)
{
    if (!isOnGround(player, world))
    {
        player.velocity.y -= 32.0f * deltaTime;
    }
    else
    {
        if (player.velocity.y < 0)
        {
            player.velocity.y = 0;
            player.position.y = std::round(player.position.y);
        }
    }
}

void PlayerMovement::update(Player &player, const World &world, float deltaTime)
{
    glm::vec3 horizontalVel = glm::vec3(player.velocity.x, 0.0f, player.velocity.z);
    float verticalVel = player.velocity.y;

    float drag = 10.0f;
    horizontalVel -= horizontalVel * drag * deltaTime;

    // std::cout << "player pos: " << player.position.x << ", " << player.position.y << ", " << player.position.z << std::endl;

    if (glm::length(horizontalVel) < 0.1f)
        horizontalVel = glm::vec3(0.0f);

    if (player.gameMode == 0)
    {
        applyGravity(player, world, deltaTime);

        verticalVel = player.velocity.y;
    }
    else if (player.gameMode == 1)
    {
        verticalVel -= verticalVel * deltaTime;

        if (std::abs(verticalVel) < 0.1f)
            verticalVel = 0.0f;
    }

    player.velocity = glm::vec3(horizontalVel.x, verticalVel, horizontalVel.z);

    float moveX = player.velocity.x * deltaTime;
    if (checkCollision(player, world, glm::vec3(moveX, 0, 0)))
    {
        player.velocity.x = 0;
        moveX = 0;
    }
    player.position.x += moveX;

    float moveZ = player.velocity.z * deltaTime;
    if (checkCollision(player, world, glm::vec3(0, 0, moveZ)))
    {
        player.velocity.z = 0;
        moveZ = 0;
    }
    player.position.z += moveZ;

    float moveY = player.velocity.y * deltaTime;
    if (checkCollision(player, world, glm::vec3(0, moveY, 0)))
    {
        if (player.velocity.y < 0)
        {
            player.velocity.y = 0;
            player.position.y = std::round(player.position.y);
        }
        else
        {
            player.velocity.y = 0;
        }
        moveY = 0;
    }
    player.position.y += moveY;

    player.syncCamera();
}