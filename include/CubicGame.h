//
// Created by ollie on 13/01/2022.
//

#ifndef CUBIC_CUBICGAME_H
#define CUBIC_CUBICGAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "./Time.h"

struct GameSettings
{
    glm::ivec2 Size;
    std::string Title;
};

class CubicGame
{
private:
    const GameSettings* _settings;
    GLFWwindow* _window;

public:
    explicit CubicGame(const GameSettings& settings);
    void Run();

    glm::ivec2 GetSize();

    virtual void Initialize();
    virtual void Update();
    virtual void Draw();
    virtual void Unload();
};


#endif //CUBIC_CUBICGAME_H
