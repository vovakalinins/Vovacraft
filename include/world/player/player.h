#pragma once
#include <glm/glm.hpp>
#include "graphics/camera.h"

class Player {
public:
    glm::vec3 position;
    glm::vec3 velocity;

    float yaw;
    float pitch;

    Camera camera;
    float eyeHeight = 1.6f;

    float weight = 100.0f;

    Player(glm::vec3 startPos);

    void syncCamera();
    glm::mat4 getViewMatrix();
};