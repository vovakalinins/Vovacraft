#pragma once
#include "world/player/player.h"
#include "world/world/world.h"
#include "world/data/blocks.h"
#include <glm/glm.hpp>

bool checkCollision(const Player& player, const World& world, glm::vec3 offset);
bool wouldBlockCollideWithPlayer(const Player& player, glm::ivec3 blockPos);
bool isOnGround(Player& player, const World& world);
float getGroundY(const Player& player, const World& world);
