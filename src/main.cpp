#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"
#include "graphics/texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include <fstream> // Required for basic file I/O
#include "core/GameState.h"
#include "core/input.h"
#include "world/world/world.h"
#include "world/generation/worldGenerator.h"
#include "graphics/renderer.h"
#include "world/player/playerMovement.h"
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float lastX = 800 / 2.0f;
// float lastY = 600 / 2.0f;
// bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(state.screenWidth, state.screenHeight, "Vovacraft", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("./assets/shaders/test.vert", "./assets/shaders/test.frag");

    glfwGetFramebufferSize(window, &state.screenWidth, &state.screenHeight);
    glViewport(0, 0, state.screenWidth, state.screenHeight);

    // unsigned int VAO = initVAO();
    // unsigned int EBO = initEBO();

    glEnable(GL_DEPTH_TEST);

    unsigned int texture1 = loadTexture("./assets/grass.jpg", false), texture2 = loadTexture("./assets/face.png", true);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    // ourShader.setInt("texture2", 1);

    // Chunk chunk(glm::vec3(0,0,0));
    WorldGenerator::generateSeededWorld(state.world, 2, 2, 123456U);

    Renderer renderer;

    renderer.updateMeshes(state.world);

    // camera
    glfwSetCursorPosCallback(window, mouse_callback);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        state.deltaTime = currentFrame - state.lastFrame;
        state.lastFrame = currentFrame;

        processInput(window);

        PlayerMovement::update(state.player, state.world, state.deltaTime);
        // PlayerMovement::applyGravity(state.player, world, state.deltaTime);

        glClearColor(73.0f / 255.0f, 129.0f / 255.0f, 235.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        glm::mat4 view = state.player.getViewMatrix();
        ourShader.setMat4("view", view);

        glm::mat4 projection;
        float aspect = (float)state.screenWidth / (float)state.screenHeight;
        projection = glm::perspective(glm::radians(state.player.camera.Zoom), aspect, 0.1f, 100.0f);

        ourShader.setMat4("projection", projection);

        renderer.render(state.player.camera, ourShader);

        // glBindVertexArray(VAO);

        // chunk.render(ourShader.ID);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &VAO);

    // glDeleteBuffers(1, &EBO);

    glDeleteProgram(ourShader.ID);

    glfwTerminate();
    return 0;
}