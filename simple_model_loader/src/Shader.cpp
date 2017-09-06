#include "Shader.hpp"

Shader::Shader()
{ }

Shader::Shader(const char * vertexShaderSource, const char * fragmentShaderSource)
{
    load(vertexShaderSource, fragmentShaderSource);
}

void Shader::load(const char * vertexShaderSource, const char * fragmentShaderSource)
{
    GLuint vertexShader, fragmentShader;
    GLint success;
    GLchar infoLog[512];

    /****************************************
     * Compile the vertex shader
    ****************************************/
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Report any errors that occurred during compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG("Error::Shader::Vertex::Compilation_Failed:\n" + std::string(infoLog));
    }
    else
        LOG("Compiled vertex shader...");

    /****************************************
     * Compile the fragment shader
    ****************************************/
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Report any errors that occurred during compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG("Error::Shader::Fragment::Compilation_Failed:\n" + std::string(infoLog));
    }
    else
        LOG("Compiled fragment shader...");

    /****************************************
     * Link the shaders to the program
    ****************************************/
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Report any errors that occurred during linking
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        LOG("Error::Shader::Program::Linking_Failed:\n" + std::string(infoLog));
    }
    else
        LOG("Linked shaders into shader program.");

    // Delete the shaders now that they have been linked to free memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    if (program != 0)
    {
        glUseProgram(program);
    }
}
