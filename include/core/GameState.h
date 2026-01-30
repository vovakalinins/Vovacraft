
#pragma once

#include "world/player/player.h"
#include "world/world/world.h"
// #include <glm/glm.hpp>

struct GameState {
  // Timing
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  // Camera/Player
  Player player;
  World world;
  float lastX = 400.0f;
  float lastY = 300.0f;
  bool firstMouse = true;

  int screenWidth = 800;
  int screenHeight = 600;

  // Hotbar
  int selectedSlot = 0;

  GameState() : player(glm::vec3(0.0f, 120.0f, 0.0f)) {
    // player.pitch = -45.0f;
    // player.syncCamera();
  }
};

extern GameState state;