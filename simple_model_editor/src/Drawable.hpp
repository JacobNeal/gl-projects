#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

class Drawable
{
    public:
        virtual void draw() = 0;
        virtual GLuint getShaderProgram() = 0;
        virtual glm::vec3 getPosition() = 0;
        virtual void setPosition(const glm::vec3 & position) = 0;
        virtual void move(const GLfloat & x, const GLfloat & y, const GLfloat & z) = 0;
        virtual void setColor(const glm::vec3 & color) = 0;
        virtual glm::vec3 getColor() = 0;
};

#endif
