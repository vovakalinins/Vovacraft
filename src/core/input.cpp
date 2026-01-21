#include "core/GameState.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    float yoffset = state.lastY - ypos; // reversed since y-coordinates go from bottom to top

    state.lastX = xpos;
    state.lastY = ypos;

    state.camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        state.camera.ProcessKeyboard(FORWARD, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        state.camera.ProcessKeyboard(BACKWARD, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        state.camera.ProcessKeyboard(LEFT, state.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        state.camera.ProcessKeyboard(RIGHT, state.deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        state.camera.ProcessKeyboard(RIGHT, state.deltaTime);
}