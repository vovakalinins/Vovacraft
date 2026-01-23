#include "world/player/player.h"

void calculateGravity(Player &player, float deltaTime)
{
    if (player.position.y > 0)
    {
        player.velocity.y -= 20.0f * deltaTime;

        if (player.velocity.y < -50.0f) player.velocity.y = -50.0f;
    }
}