#include "System.hpp"

System::System(const SystemType & type, const Bitmask & requirements)
    : m_type(type), m_requirementMask(requirements)
{ }

bool System::addEntity(Entity * entity)
{
    bool added = false;

    if (!hasEntity(entity))
    {
        m_entities.push_back(entity);
        added = true;
    }

    return added;
}

bool System::removeEntity(Entity * entity)
{
    bool removed = false;

    for (std::vector<Entity *>::iterator iter = m_entities.begin();
         removed == false && iter != m_entities.end(); ++iter)
    {
        if ((*iter) == entity)
        {
            m_entities.erase(iter);
            removed = true;
        }
    }

    return removed;
}

bool System::hasEntity(Entity * entity)
{
    bool found = false;

    for (std::vector<Entity *>::iterator iter = m_entities.begin();
         found == false && iter != m_entities.end(); ++iter)
    {
        if ((*iter) == entity)
            found = true;
    }
    
    return found;
}

void System::clearEntities()
{
    m_entities.clear();
}

Bitmask System::getRequirements()
{
    return m_requirementMask;
}
