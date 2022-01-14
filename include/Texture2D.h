//
// Created by ollie on 13/01/2022.
//

#ifndef CUBIC_TEXTURE2D_H
#define CUBIC_TEXTURE2D_H

#include <string>
#include "stb_image.h"
#include "glm/glm.hpp"
#include <glad/glad.h>

class Texture2D
{
private:
    GLuint _handle;
    glm::ivec2 _size;

public:
    explicit Texture2D(const char* path);
    ~Texture2D();

    void Bind();

    glm::ivec2 Size();
};


#endif //CUBIC_TEXTURE2D_H
