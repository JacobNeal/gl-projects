#include "BaseComp.hpp"

BaseComp::BaseComp(const Component & type)
    : m_type(type)
{ }

Component BaseComp::getType()
{
    return m_type;
}
