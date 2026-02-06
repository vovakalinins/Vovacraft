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
    return glm::normalize(glm::cross(getBodyForward(player), glm::vec3(0, 1, 0)));
}

void PlayerMovement::moveForward(Player &player, float deltaTime)
{
    player.velocity += getBodyForward(player) * WALK_SPEED * deltaTime;
}

void PlayerMovement::moveBackward(Player &player, float deltaTime)
{
    player.velocity -= getBodyForward(player) * WALK_SPEED * deltaTime;
}

void PlayerMovement::moveLeft(Player &player, float deltaTime)
{
    player.velocity -= getBodyRight(player) * WALK_SPEED * deltaTime;
}

void PlayerMovement::moveRight(Player &player, float deltaTime)
{
    player.velocity += getBodyRight(player) * WALK_SPEED * deltaTime;
}

void PlayerMovement::flyUp(Player &player, float deltaTime)
{
    player.velocity.y += FLY_SPEED * deltaTime;
}

void PlayerMovement::jump(Player &player, const World &world)
{
    if (isOnGround(player, world) && player.velocity.y <= 0)
    {
        player.velocity.y = JUMP_FORCE;
    }
}

void PlayerMovement::sneak(Player &player, const World &world) {}

void PlayerMovement::flyDown(Player &player, float deltaTime)
{
    player.velocity.y -= FLY_SPEED * deltaTime;
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

void PlayerMovement::update(Player &player, const World &world, float deltaTime)
{
    glm::vec3 hVel(player.velocity.x, 0, player.velocity.z);
    hVel *= (1.0f - 10.0f * deltaTime);
    if (glm::length(hVel) < 0.01f)
        hVel = glm::vec3(0);

    float vVel = player.velocity.y;

    if (player.gameMode == 0)
    {
        vVel -= 28.0f * deltaTime;
        if (vVel < -50.0f)
            vVel = -50.0f;
    }
    else
    {
        vVel *= (1.0f - 5.0f * deltaTime);
        if (std::abs(vVel) < 0.1f)
            vVel = 0;
    }

    player.velocity = glm::vec3(hVel.x, vVel, hVel.z);

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
    glm::vec3 newPos = player.position + glm::vec3(0, moveY, 0);

    if (checkCollision(player, world, glm::vec3(0, moveY, 0)))
    {
        if (player.velocity.y < 0)
        {
            float groundY = getGroundY(player, world);
            player.position.y = groundY;
            player.velocity.y = 0;
        }
        else
        {
            player.velocity.y = 0;
        }
    }
    else
    {
        player.position.y += moveY;
    }

    // std::cout << "player pos " << player.position.x << ", " << player.position.y << ", " << player.position.z << std::endl;

    player.syncCamera();
}
