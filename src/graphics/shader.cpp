#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

// const char *vertexShaderSource = "#version 330 core\n"
//                                  "layout (location = 0) in vec3 aPos;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                  "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                    "}\0";

// clean this up
std::string getShaderSourceFromFile(std::string filename);

unsigned int initVertexShader()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertShaderStr = getShaderSourceFromFile("./assets/shaders/test.vert");
    const GLchar *vertShaderSrc = vertShaderStr.c_str();

    glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILIATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    return vertexShader;
}

unsigned int initFragmentShader()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragShaderStr = getShaderSourceFromFile("./assets/shaders/test.frag");
    const GLchar *fragShaderSrc = fragShaderStr.c_str();

    glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILIATION_FAILED\n"
                  << infoLog << std::endl;
        return -1;
    }

    return fragmentShader;
}

unsigned int initShaderProgram()
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    unsigned int vertexShader = initVertexShader();

    unsigned int fragmentShader = initFragmentShader();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "FAILED ATTACHING SHADERS\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void useShaders(unsigned int program)
{
    glUseProgram(program);
}

// Source - https://stackoverflow.com/a
// Posted by Val Zubko
// Retrieved 2026-01-20, License - CC BY-SA 4.0

std::string getShaderSourceFromFile(std::string filename)
{
    std::string result;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "SHADER FILE: Could not open shader file at: " << filename << std::endl;
        return "";
    }

    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);
        result += line + '\n';
    }

    file.close();

    return result;
}
