#include "core/input.h"
#include "core/GameState.h"
#include "world/player/playerMovement.h" // Include the logic

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (state.firstMouse) {
        state.lastX = xpos;
        state.lastY = ypos;
        state.firstMouse = false;
    }

    float xoffset = xpos - state.lastX;
    float yoffset = state.lastY - ypos; 
    state.lastX = xpos;
    state.lastY = ypos;

    // Delegate to Logic System
    PlayerMovement::look(state.player, xoffset, yoffset);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Map Keys to Logic Functions
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        PlayerMovement::moveForward(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        PlayerMovement::moveBackward(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        PlayerMovement::moveLeft(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        PlayerMovement::moveRight(state.player, state.deltaTime);
        
    // Debug Fly
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        PlayerMovement::flyUp(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        PlayerMovement::flyDown(state.player, state.deltaTime);
}