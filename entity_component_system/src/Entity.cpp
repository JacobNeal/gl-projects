#include "Entity.hpp"

Entity::Entity(const std::bitset<NUM_COMPONENT_TYPES> & mask)
    : m_componentMask(mask)
{
    for (unsigned int count = 0; count < NUM_COMPONENT_TYPES; ++count)
    {
        if (m_componentMask[count])
        {
            addComponent((ComponentType)count);
        }
    }
}

Entity::Entity()
{ }

Entity::~Entity()
{
    while (m_components.begin() != m_components.end())
    {
        delete (*m_components.begin());
        m_components.erase(m_components.begin());
    }
}

bool Entity::addComponent(Component * component)
{
    bool added = false;

    if (!hasComponent(component->getType()))
    {
        m_components.push_back(component);
        m_componentMask.set((unsigned int)component->getType());
        added = true;
    }

    return added;
}

bool Entity::removeComponent(const ComponentType & compType)
{
    bool removed = false;

    if (hasComponent(compType))
    {
        for (std::vector<Component *>::iterator citer = m_components.begin();
             citer != m_components.end(); ++citer)
        {
            if ((*citer)->getType() == compType)
            {
                m_components.erase(citer);
                m_componentMask.reset((unsigned int)compType);
                removed = true;
            }
        }
    }

    return removed;
}

bool Entity::hasComponent(const ComponentType & compType)
{
    return m_componentMask[(unsigned int)compType];
}

std::bitset<NUM_COMPONENT_TYPES> Entity::getComponentMask()
{
    return m_componentMask;
}
