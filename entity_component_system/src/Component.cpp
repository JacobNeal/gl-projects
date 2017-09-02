#include "Component.hpp"

Component::Component(const ComponentType & type)
    : m_type(type)
{ }

ComponentType Component::getType()
{
    return m_type;
}
