
#pragma once

#include "world/player/player.h"
#include "world/world/world.h"
#include <glm/glm.hpp>

struct GameState {
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  Player player;
  World world;
  float lastX = 400.0f;
  float lastY = 300.0f;
  bool firstMouse = true;

  int screenWidth = 800;
  int screenHeight = 600;

  int selectedSlot = 0;

  glm::ivec3 breakTarget = glm::ivec3(0, -9999, 0);
  int breakFace = 0;
  float breakProgress = 0.0f;
  bool breakValid = false;
  float breakCooldownRemaining = 0.0f;

  GameState() : player(){};
};

extern GameState state;