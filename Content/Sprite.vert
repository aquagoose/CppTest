#version 330 core

in vec2 aPosition;
in vec2 aTexCoords;

out vec2 frag_texCoords;

uniform mat4 uProjectionView;

void main()
{
    gl_Position = vec4(aPosition, 0.0, 1.0) * uProjectionView;
    frag_texCoords = aTexCoords;
}