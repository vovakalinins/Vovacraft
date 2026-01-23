#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float ZOOM        =  70.0f;

// A "Dumb" Camera class.
// It simply holds position/rotation data and calculates the View Matrix.
class Camera
{
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    // Euler Angles
    float Yaw;
    float Pitch;
    
    // Camera options (Field of View)
    float Zoom;

    // Constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Calculates the front vector from the Camera's current Euler Angles.
    // Call this manually after modifying Yaw or Pitch!
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        
        // Re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp)); 
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif