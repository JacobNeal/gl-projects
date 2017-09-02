#ifndef POSITION_COMP_HPP
#define POSITION_COMP_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "BaseComp.hpp"

class PositionComp : public BaseComp
{
    public:
        PositionComp();

        virtual void read(std::stringstream & stream);

        const glm::vec3 & getPosition();
        void setPosition(const glm::vec3 & position);

        void move(GLfloat x, GLfloat y, GLfloat z);
        void move(const glm::vec3 & vec);

    private:
        /****************************************
         * Data members
        ****************************************/
        glm::vec3 m_position;
};

#endif
