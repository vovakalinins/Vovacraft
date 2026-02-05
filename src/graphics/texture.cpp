#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int loadTexture(const char *path, bool isTransparent)
{
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int imgwidth, imgheight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &imgwidth, &imgheight, &nrChannels, 0);
    if (data)
    {
        if (isTransparent)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);

    return texture1;
}

unsigned int loadUITexture(const char *path)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int imgwidth, imgheight, nrChannels;
    stbi_set_flip_vertically_on_load(false);

    unsigned char *data = stbi_load(path, &imgwidth, &imgheight, &nrChannels, 4);

    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgwidth, imgheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        std::cout << "Loaded UI texture: " << path << " (" << imgwidth << "x" << imgheight << ")" << std::endl;
    }
    else
    {
        std::cout << "Failed to load UI texture: " << path << std::endl;
    }
    stbi_image_free(data);

    stbi_set_flip_vertically_on_load(true);

    return texture;
}