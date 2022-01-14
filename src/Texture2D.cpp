//
// Created by ollie on 13/01/2022.
//

#include "../include/Texture2D.h"

Texture2D::Texture2D(const char* path)
{
    int x, y, n;
    unsigned char* data = stbi_load(path, &x, &y, &n, 0);

    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    _size = glm::ivec2(x, y);

    stbi_image_free(data);
}

void Texture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _handle);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &_handle);
}

glm::ivec2 Texture2D::Size()
{
    return _size;
}