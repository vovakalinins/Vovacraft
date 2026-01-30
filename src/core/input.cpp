#include "core/input.h"
#include "core/GameState.h"
#include "world/player/playerActions.h"
#include "world/player/playerMovement.h"
#include <iostream>

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (state.firstMouse)
    {
        state.lastX = xpos;
        state.lastY = ypos;
        state.firstMouse = false;
    }

    float xoffset = xpos - state.lastX;
    float yoffset = state.lastY - ypos;
    state.lastX = xpos;
    state.lastY = ypos;

    PlayerMovement::look(state.player, xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        PlayerActions::breakBlock(state.player, state.world);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        PlayerActions::placeBlock(state.player, state.world);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    state.selectedSlot -= (int)yoffset;

    if (state.selectedSlot < 0)
        state.selectedSlot = 8;
    if (state.selectedSlot > 8)
        state.selectedSlot = 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        PlayerMovement::moveForward(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        PlayerMovement::moveBackward(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        PlayerMovement::moveLeft(state.player, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        PlayerMovement::moveRight(state.player, state.deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (state.player.gameMode == 1)
        {
            PlayerMovement::flyUp(state.player, state.deltaTime);
            return;
        }
        PlayerMovement::jump(state.player, state.world);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        if (state.player.gameMode == 1)
        {
            PlayerMovement::flyDown(state.player, state.deltaTime);
            return;
        }
    }

    // state.player.isSneaking = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        state.selectedSlot = 0;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        state.selectedSlot = 1;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        state.selectedSlot = 2;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        state.selectedSlot = 3;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        state.selectedSlot = 4;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        state.selectedSlot = 5;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        state.selectedSlot = 6;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        state.selectedSlot = 7;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        state.selectedSlot = 8;
}