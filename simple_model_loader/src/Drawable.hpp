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
};

#endif
