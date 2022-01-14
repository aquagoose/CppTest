//
// Created by ollie on 13/01/2022.
//

#include "../include/CubicGame.h"

#include <iostream>

CubicGame::CubicGame(const GameSettings& settings)
{
    _settings = &settings;
}

void CubicGame::Run()
{
    if (!glfwInit())
    {
        std::cout << "GLFW could not initialise" << std::endl;
        throw std::exception();
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    _window = glfwCreateWindow(_settings->Size.x, _settings->Size.y, _settings->Title.c_str(), nullptr, nullptr);
    if (!_window)
    {
        std::cout << "Window could not be created.";
        glfwTerminate();
        throw std::exception();
    }

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);
    glfwSetWindowPos(_window, monitorX + mode->width / 2 - _settings->Size.x / 2, monitorY + mode->height / 2 - _settings->Size.y / 2);

    Initialize();

    glViewport(0, 0, _settings->Size.x, _settings->Size.y);

    glfwShowWindow(_window);

    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        Update();
        Draw();

        glfwSwapBuffers(_window);
    }

    glfwTerminate();
}

void CubicGame::Initialize()
{}

void CubicGame::Update()
{}

void CubicGame::Draw()
{}

void CubicGame::Unload()
{}

glm::ivec2 CubicGame::GetSize()
{
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return glm::ivec2(width, height);
}
