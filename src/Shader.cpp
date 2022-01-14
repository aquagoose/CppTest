//
// Created by ollie on 13/01/2022.
//

#include "../include/Shader.h"

#include <fstream>
#include <sstream>

Shader::Shader(const char *vertex, const char *fragment, LoadType type)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    switch (type)
    {
        case LoadType::String:
            glShaderSource(vertexShader, 1, &vertex, nullptr);
            glShaderSource(fragmentShader, 1, &fragment, nullptr);
            break;
        case LoadType::File:
            std::ifstream vFile, fFile;
            std::stringstream vStream, fStream;

            vFile.open(vertex);
            fFile.open(fragment);
            vStream << vFile.rdbuf();
            fStream << fFile.rdbuf();
            vFile.close();
            fFile.close();

            std::string vCode = vStream.str();
            std::string fCode = fStream.str();

            const char* vertexCode = vCode.c_str();
            const char* fragmentCode = fCode.c_str();

            glShaderSource(vertexShader, 1, &vertexCode, nullptr);
            glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);

            break;
    }

    Compile(vertexShader);
    Compile(fragmentShader);

    _handle = glCreateProgram();
    glAttachShader(_handle, vertexShader);
    glAttachShader(_handle, fragmentShader);
    Link(_handle);
    glDetachShader(_handle, vertexShader);
    glDetachShader(_handle, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /*int numLocations;
    glGetProgramiv(_handle, GL_ACTIVE_UNIFORMS, &numLocations);

    char name[64];

    for (int i = 0; i < numLocations; i++)
    {
        glGetActiveUniform(_handle, i, 64, nullptr, nullptr, nullptr, name);
        GLint location = glGetUniformLocation(_handle, name);
        _locations.insert({name, location});
    }*/
}

void Shader::Compile(GLuint shader)
{
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cout << "Error while compiling shader '" << shader << "'\n" << info << std::endl;
        throw std::exception();
    }
}

void Shader::Link(GLuint program)
{
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::cout << "Error while linking program '" << program << "'\n" << info << std::endl;
        throw std::exception();
    }
}

void Shader::Use()
{
    glUseProgram(_handle);
}

Shader::~Shader()
{
    glDeleteProgram(_handle);
}

GLint Shader::GetUniform(const char *name)
{
    //return _locations[name];
    return glGetUniformLocation(_handle, name);
}

void Shader::SetUniform(const char *name, float value)
{
    GLint location = GetUniform(name);
    glUniform1f(location, value);
}

void Shader::SetUniform(const char *name, glm::vec2 value)
{
    GLint location = GetUniform(name);
    glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char *name, glm::vec3 value)
{
    GLint location = GetUniform(name);
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char *name, glm::vec4 value)
{
    GLint location = GetUniform(name);
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char *name, glm::mat4 value)
{
    GLint location = GetUniform(name);
    glUniformMatrix4fv(location, 1, GL_TRUE, glm::value_ptr(value));
}

GLuint Shader::GetAttribLocation(const char *name)
{
    return glGetAttribLocation(_handle, name);
}
