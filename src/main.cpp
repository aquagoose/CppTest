#include "../include/CubicGame.h"
#include "../include/Texture2D.h"
#include "../include/SpriteRenderer.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class MyGame : public CubicGame
{
private:
    Texture2D* _texture;
    SpriteRenderer* _renderer;

    glm::vec2 _pos;

public:
    using CubicGame::CubicGame;

    void Initialize() override
    {
        glClearColor((float) 100 / 255, (float) 149 / 255, (float) 237 / 255, 1.0);

        _renderer = new SpriteRenderer(glm::ivec2(1280, 720));

        _texture = new Texture2D("Content/awesomeface.png");
        _pos = glm::vec2(0);
    }

    void Update() override
    {
        _pos += glm::vec2(1);
    }

    void Draw() override
    {
        _renderer->Begin();
        _renderer->Draw(_texture, _pos, glm::vec4(0, 0, 512, 512));
        _renderer->End();
    }

    void Unload() override
    {
        delete _texture;
        delete _renderer;
    }
};

int main()
{
    GameSettings settings;
    settings.Size = glm::ivec2(1280, 720);
    settings.Title = "My Game!";
    MyGame game = MyGame(settings);
    game.Run();

    return 0;
}
