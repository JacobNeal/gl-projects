#ifndef POSITION_COMP_HPP
#define POSITION_COMP_HPP

#include <iostream>
#include <glm/glm.hpp>

#include "Component.hpp"
#include "Logger.hpp"

class PositionComp : public Component
{
    public:
        PositionComp()
            : Component(ComponentType::Position), m_position(glm::vec3(0.0f, 0.0f, 0.0f))
        { }

        glm::vec3 getPosition() const
        {
            return m_position;
        }

        void setPosition(const glm::vec3 & position)
        {
            m_position = position;
        }

        void move(const glm::vec3 & position)
        {
            m_position += position;
        }

        void move(float x, float y, float z)
        {
            m_position.x += x;
            m_position.y += y;
            m_position.z += z;
        }

        virtual void read(std::stringstream & stream)
        {
            stream >> m_position.x;
            stream >> m_position.y;
            stream >> m_position.z;
        }

    private:
        /****************************************
         * Data members
        ****************************************/
        glm::vec3 m_position;
};

#endif
