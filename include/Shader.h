//
// Created by ollie on 13/01/2022.
//

#ifndef CUBIC_SHADER_H
#define CUBIC_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>

enum struct LoadType
{
    String,
    File
};

class Shader
{
private:
    GLuint _handle;

    void Compile(GLuint shader);
    void Link(GLuint program);

    std::map<const char*, GLint> _locations;

    GLint GetUniform(const char* name);

public:
    Shader(const char* vertex, const char* fragment, LoadType type = LoadType::File);
    ~Shader();
    void Use();
    GLuint GetAttribLocation(const char* name);

    void SetUniform(const char* name, float value);
    void SetUniform(const char* name, glm::vec2 value);
    void SetUniform(const char* name, glm::vec3 value);
    void SetUniform(const char* name, glm::vec4 value);
    void SetUniform(const char* name, glm::mat4 value);
};

#endif //CUBIC_SHADER_H
