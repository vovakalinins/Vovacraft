#pragma once
#include <glm/glm.hpp>
#include "graphics/camera.h"
#include "world/player/inventory.h"

class Player
{
public:
    glm::vec3 position;
    glm::vec3 velocity;

    float yaw;
    float pitch;

    Camera camera;
    float eyeHeight = 1.8f;

    float height = 1.8f;
    float width = 0.6f;
    float weight = 100.0f;

    int gameMode = 0; // 0s 1c
    int health = 20;

    bool isFlying = false;
    bool isSneaking = false;
    bool isRunning = false;

    Player(glm::vec3 startPos);

    Inventory inventory;

    void syncCamera();
    glm::mat4 getViewMatrix();
};