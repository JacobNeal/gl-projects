#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Drawable.hpp"
#include "Shader.hpp"

class Triangle : public Drawable
{
    public:
        Triangle(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), GLfloat size = 1.0f);
        ~Triangle();

        virtual void draw();

    private:
        /****************************************
         * Data members
        ****************************************/
        GLuint     m_VBO;
        GLuint     m_VAO;

        glm::vec3  m_position;
        GLfloat    m_scale;

        Shader     m_shader;
};

#endif
