#include "graphics/ui_renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

UIRenderer::UIRenderer() : uiShader(nullptr), VAO(0), VBO(0) {}

UIRenderer::~UIRenderer()
{
    if (uiShader)
        delete uiShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void UIRenderer::init()
{
    uiShader = new Shader("./assets/shaders/ui.vert", "./assets/shaders/ui.frag");

    float vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void UIRenderer::renderQuad(float x, float y, float width, float height)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    uiShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UIRenderer::renderHotbar(unsigned int hotbarTexture, unsigned int selectionTexture,
                              int selectedSlot, int screenWidth, int screenHeight)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    uiShader->use();

    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
    uiShader->setMat4("projection", projection);

    glBindVertexArray(VAO);

    float scale = 2.0f;
    float hotbarWidth = 366.0f * scale;
    float hotbarHeight = 44.0f * scale;

    float hotbarX = (screenWidth - hotbarWidth) / 2.0f;
    float hotbarY = 20.0f;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hotbarTexture);
    uiShader->setInt("uiTexture", 0);

    renderQuad(hotbarX, hotbarY, hotbarWidth, hotbarHeight);

    float selectionWidth = 24.0f * scale * 2;
    float selectionHeight = 24.0f * scale * 2;

    float slotWidth = 40.0f * scale;
    float slotStartX = 3.0f * scale;

    float slotCenterX = hotbarX + slotStartX + (selectedSlot * slotWidth) + (slotWidth / 2.0f);
    float selectionX = slotCenterX - (selectionWidth / 2.0f);

    float selectionY = hotbarY + (hotbarHeight - selectionHeight) / 2.0f - 1.0f * scale;

    glBindTexture(GL_TEXTURE_2D, selectionTexture);
    renderQuad(selectionX, selectionY, selectionWidth, selectionHeight);

    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void UIRenderer::renderCrosshair(unsigned int crosshairTexture, int screenWidth, int screenHeight)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    uiShader->use();
    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
    uiShader->setMat4("projection", projection);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, crosshairTexture);
    uiShader->setInt("uiTexture", 0);

    float size = 48.0f;
    float x = (screenWidth - size) / 2.0f;
    float y = (screenHeight - size) / 2.0f;
    renderQuad(x, y, size, size);

    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}
