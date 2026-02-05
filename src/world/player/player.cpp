#include "world/player/player.h"

Player::Player() 
    : velocity(0.0f), yaw(-90.0f), pitch(0.0f) 
{
    syncCamera();
}

void Player::syncCamera() {
    camera.Position = position + glm::vec3(0, eyeHeight, 0);

    camera.Yaw = this->yaw;
    camera.Pitch = this->pitch;
    
    camera.updateCameraVectors();
}

glm::mat4 Player::getViewMatrix() {
    return camera.GetViewMatrix();
}