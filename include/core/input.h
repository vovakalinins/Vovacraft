#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);