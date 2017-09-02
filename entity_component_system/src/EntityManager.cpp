#include "EntityManager.hpp"

EntityManager::EntityManager()
    : m_num_entities(0)
{ }

unsigned int EntityManager::addEntity(const std::bitset<NUM_COMPONENT_TYPES> & mask)
{
    unsigned int entityId = m_num_entities;

    if (m_entities.emplace(entityId, EntityData(0, ComponentContainer())).second)
    {
        ++m_numEntities;

        for (unsigned int count = 0; count < NUM_COMPONENT_TYPES; ++count)
        {
            if (mask[count])
                addComponent(entityId, (Component)count);
        }

        // Notify the system manager of a modified entity

        ++m_numEntities;
    }
    else
        entityId = -1;

    return entityId;
}

bool EntityManager::removeEntity(const unsigned int & entity, const Component & compType)
{
    EntityContainer::iterator iter = m_entities.find(entity);
    bool removed = false;

    if (iter != m_entities.end())
    {
        // Remove all components
        while (iter->second.second.begin() != iter->second.second.end())
        {
            // Since this is a BaseComp pointer, deallocate it's memory
            delete iter->second.second.back();
            iter->second.second.pop_back();
        }
        
        m_entities.erase(iter);

        // Remove the entity from the system manager
        
        --m_numEntities; 
        removed = true;
    }

    return removed;
}

bool EntityManager::addComponent(const unsigned int & entity, const Component & compType)
{
    EntityContainer::iterator iter = m_entities.find(entity);
    bool added = false;

    if (iter != m_entities.end())
    {
        // Check to make sure the entity doesn't already have the component using the bitset
        if (!iter->second.first[(unsigned int)compType])
        {
            // Make sure the component type exists
            ComponentFactory::iterator citer = m_factory.find(compType);

            if (citer != m_factory.end())
            {
                BaseComp * comp = citer->second();
                
                iter->second.second.emplace_back(comp);
                iter->second.first.set((unsigned int)compType);

                // Notify the system manager of a modified entity

                added = true;
            }
        }
    }

    return added;
}

bool EntityManager::removeComponent(const unsigned int & entity, const Component & compType)
{
    EntityContainer::iterator iter = m_entities.find(entity);
    bool removed = false;

    if (iter != m_entities.end())
    {
        // Check to make sure the entity has the component using the bitset
        if (iter->second.first[(unsigned int)compType])
        {
            for (ComponentContainer::iterator citer = iter->second.second.begin();
                 remove == false && citer != iter->second.second.end(); ++citer)
            {
                if (citer->getType() == compType)
                {
                    delete (*citer);
                    iter->second.second.erase(citer);
                    iter->second.first.reset((unsigned int)compType);
                    
                    // Notify the system manager of a modified entity

                    removed = true;
                }
            }
        }
    }

    return removed;
}

bool EntityManager::hasComponent(const unsigned int & entity, const Component & compType)
{
    EntityContainer::iterator iter = m_entities.find(entity);
    bool found = false;

    if (iter != m_entities.end())
    {
        found = iter->second.first[(unsigned int)compType];
    }

    return found;
}

void EntityManager::purge()
{
    // Notify the system manager to purge all entities

    for (EntityContainer::iterator iter = m_entities.begin();
         iter != m_entities.end(); ++iter)
    {
        while (iter->second.second.begin() != iter->second.second.end())
        {
            // Since this is a BaseComp pointer, deallocate it's memory
            delete iter->second.second.back();
            iter->second.second.pop_back();
        }

        // Clear all components
        iter->second.second.clear();
    }

    m_entities.clear();
    m_numEntities = 0;
}
