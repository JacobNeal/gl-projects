#include "PositionComp.hpp"

PositionComp::PositionComp()
    : BaseComp(Component::Position), m_position(0.0f, 0.0f, 0.0f)
{ }

void PositionComp::read(std::stringstream & stream)
{
    stream >> m_position.x >> m_position.y >> m_position.z;
}

const glm::vec3 & PositionComp::getPosition()
{
    return m_position;
}

void PositionComp::setPosition(const glm::vec3 & position)
{
    m_position = position;
}

void PositionComp::move(GLfloat x, GLfloat y, GLfloat z)
{
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
}

void PositionComp::move(const glm::vec3 & vec)
{
    m_position += vec;
}
