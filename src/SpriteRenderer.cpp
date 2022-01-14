//
// Created by ollie on 13/01/2022.
//

#include "../include/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(glm::ivec2 size)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, MaxSprites * VerticesCount, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxSprites * IndicesCount, nullptr, GL_DYNAMIC_DRAW);

    _shader = new Shader("Content/Sprite.vert", "Content/Sprite.frag");
    _shader->Use();

    GLuint vertexLocation = _shader->GetAttribLocation("aPosition");
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

    GLuint texCoordsLocation = _shader->GetAttribLocation("aTexCoords");
    glEnableVertexAttribArray(texCoordsLocation);
    glVertexAttribPointer(texCoordsLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    _projection = glm::ortho(0.0f, (float) size.x, (float) size.y, 0.0f, -1.0f, 1.0f);

    _begun = false;
    _currentSprite = 0;
}

void SpriteRenderer::Begin(glm::mat4 transform)
{
    if (_begun)
    {
        std::cout << "Sprite renderer has already begun." << std::endl;
        throw std::exception();
    }

    _begun = true;

    _shader->Use();
    _shader->SetUniform("uProjectionView", _projection * transform);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
}

void SpriteRenderer::End()
{
    if (!_begun)
    {
        std::cout << "Sprite renderer has not begun!!" << std::endl;
        throw std::exception();
    }

    _begun = false;
    Flush();
}

void SpriteRenderer::Draw(Texture2D *texture, glm::vec2 position, glm::vec4 source)
{
    if (_currentTexture != texture)
        Flush();

    _currentTexture = texture;

    glm::ivec2 size = texture->Size();

    float texOffsetX = source.x / (float) size.x;
    float texOffsetY = 1 - (source.y + source.w) / (float) size.y;
    float texOffsetW = texOffsetX + source.z / (float) size.x;
    float texOffsetH = texOffsetY + source.w / (float) size.y;

    texOffsetH *= -1.0f;

    float quads[] =
            {
            position.x + source.z, position.y + source.w,
            texOffsetW, texOffsetY,

            position.x + source.z, position.y,
            texOffsetW, texOffsetH,

            position.x, position.y,
            texOffsetX, texOffsetH,

            position.x, position.y + source.z,
            texOffsetX, texOffsetY
            };

    glBufferSubData(GL_ARRAY_BUFFER, _currentSprite * VerticesCount, VerticesCount, quads);

    GLuint indices[] =
            {
            4 * _currentSprite, 1 + 4 * _currentSprite, 3 + 4 * _currentSprite,
            1 + 4 * _currentSprite, 2 + 4 * _currentSprite, 3 + 4 * _currentSprite
            };

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _currentSprite * IndicesCount, IndicesCount, indices);

    _currentSprite++;
}

void SpriteRenderer::Flush()
{
    if (_currentSprite == 0)
        return;

    _currentTexture->Bind();

    glDrawElements(GL_TRIANGLES, (GLsizei) (_currentSprite * 6), GL_UNSIGNED_INT, nullptr);

    _currentSprite = 0;
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    delete _shader;
}