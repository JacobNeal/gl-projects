#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <string>
#include <GL/glew.h>

class Shader
{
    public:
        GLuint program;

        Shader();
        Shader(const char * vertexShaderSource, const char * fragmentShaderSource);

        void load(const char * vertexShaderSource, const char * fragmentShaderSource);
        void use();
};

#endif
