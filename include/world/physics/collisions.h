#pragma once
#include "world/player/player.h"
#include "world/world/world.h"
#include "world/data/blocks.h"
#include <glm/glm.hpp>

bool checkCollision(const Player& player, const World& world, glm::vec3 offset);
bool isOnGround(Player& player, const World& world);
