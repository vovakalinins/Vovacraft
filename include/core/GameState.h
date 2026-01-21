
#pragma once

#include "graphics/camera.h"
#include <glm/glm.hpp>

struct GameState {
    // Timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Camera/Player
    Camera camera;
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;

    // Window settings
    int screenWidth = 800;
    int screenHeight = 600;

    // Constructor to initialize camera position
    GameState() : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}
};

// Declare a global instance so other files can see it
extern GameState state;