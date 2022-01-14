//
// Created by ollie on 13/01/2022.
//

#ifndef CUBIC_SPRITERENDERER_H
#define CUBIC_SPRITERENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "./Texture2D.h"
#include "./Shader.h"
#include <iostream>

class SpriteRenderer
{
private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    unsigned int _currentSprite;
    Texture2D* _currentTexture;
    Shader* _shader;

    const unsigned int MaxSprites = 512;
    const unsigned int VerticesCount = 16 * sizeof(float);
    const unsigned int IndicesCount = 6 * sizeof(GLuint);

    bool _begun;

    glm::mat4 _projection;

    void Flush();

public:
    SpriteRenderer(glm::ivec2 size);
    ~SpriteRenderer();

    void Begin(glm::mat4 transform = glm::mat4(1.0));
    void End();
    void Draw(Texture2D* texture, glm::vec2 position, glm::vec4 source);
};


#endif //CUBIC_SPRITERENDERER_H
