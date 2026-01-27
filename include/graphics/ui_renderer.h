#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "graphics/shader.h"

class UIRenderer
{
public:
    UIRenderer();
    ~UIRenderer();

    void init();
    void renderHotbar(unsigned int hotbarTexture, unsigned int selectionTexture,
                      int selectedSlot, int screenWidth, int screenHeight);

private:
    unsigned int VAO, VBO;
    Shader *uiShader;

    void renderQuad(float x, float y, float width, float height);
};
