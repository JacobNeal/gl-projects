#include "Component.hpp"

Component::Component(const ComponentType & type)
    : m_type(type)
{ }

Component::~Component()
{ }

ComponentType Component::getType()
{
    return m_type;
}
