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
#include "world/data/blocks.h"
#include "graphics/ui_renderer.h"
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float lastX = 800 / 2.0f;
// float lastY = 600 / 2.0f;
// bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    state.screenWidth = width;
    state.screenHeight = height;
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
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    unsigned int texture1 = loadTexture("./assets/blockatlas.png", true);

    ourShader.use();
    ourShader.setInt("texture1", 0);

    initBlockDatabase();

    // Chunk chunk(glm::vec3(0,0,0));
    srand(static_cast<unsigned int>(time(0)));
    uint_fast32_t ranSeed = static_cast<uint_fast32_t>(rand() % 101);

    WorldGenerator::generateSeededWorld(state.world, 4, 4, ranSeed);
    state.world.computeSpawn();
    state.player.position = glm::vec3(
        state.world.worldSpawn.x,
        state.world.worldSpawn.y+1,
        state.world.worldSpawn.z);
    state.player.syncCamera();

    Renderer renderer;
    UIRenderer uiRenderer;
    uiRenderer.init();
    unsigned int hotbarTexture = loadUITexture("./assets/Hotbar.png");
    unsigned int selectionTexture = loadUITexture("./assets/Hotbar_selection.png");
    unsigned int crosshairTexture = loadUITexture("./assets/Crosshair.png");

    renderer.updateMeshes(state.world);

    // camera
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        state.deltaTime = currentFrame - state.lastFrame;
        state.lastFrame = currentFrame;

        processInput(window);

        PlayerMovement::update(state.player, state.world, state.deltaTime);
        // PlayerMovement::applyGravity(state.player, world, state.deltaTime);

        renderer.updateMeshes(state.world);

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
        projection = glm::perspective(glm::radians(state.player.camera.Zoom), aspect, 0.1f, 500.0f);

        ourShader.setMat4("projection", projection);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        renderer.render(state.player.camera, ourShader,
            state.breakTarget, state.breakFace, state.breakProgress, state.breakValid);

        glDisable(GL_BLEND);

        uiRenderer.renderHotbar(hotbarTexture, selectionTexture, state.selectedSlot,
                                state.screenWidth, state.screenHeight);
        uiRenderer.renderCrosshair(crosshairTexture, state.screenWidth, state.screenHeight);

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