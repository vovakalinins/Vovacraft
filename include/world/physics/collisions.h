#include "world/player/player.h"
#include <glm/glm.hpp>
#include "world/world/world.h"

bool checkCollision(const Player &player, const World &world, glm::vec3 offset);
bool isOnGround(Player &player, const World &world);