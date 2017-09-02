#include "EntityManager.hpp"

EntityManager::EntityManager(SystemManager * sysManager)
    : m_sysManager(sysManager), m_componentLock(false)
{
    //Component Type Example (to associate a ComponentType with a constructor):
    //addComponentType<PositionComp>(ComponentType::Position);
}

EntityManager::~EntityManager()
{
    purge();
}

void EntityManager::addEntity(Bitmask mask)
{
    LOG("Adding entity...");

    m_componentLock = true;
    m_entities.push_back(new Entity);

    for (unsigned int bit = 0; bit < NUM_COMPONENT_TYPES; ++bit)
    {
        LOG("Checking bit: " + std::to_string(bit));
        if (mask.getBit(bit))
        {
            LOG("Bit set for bit: " + std::to_string(bit));
            addComponent(m_entities.size() - 1, (ComponentType)bit);
        }
    }

    m_sysManager->addEntity(m_entities.back());
}

void EntityManager::addEntity(const std::string & entityFile)
{ }

bool EntityManager::removeEntity(const unsigned int & entity)
{
    bool removed = false;

    if (entity < m_entities.size())
    {
        Entity * ent = m_entities[entity];
        m_sysManager->removeEntity(ent);

        for (Component * entityComp : ent->components)
            delete entityComp;

        ent->components.clear();
        delete ent;

        m_entities.erase(m_entities.begin() + entity);
        removed = true;
    }

    return removed;
}

bool EntityManager::addComponent(const unsigned int & entity, const ComponentType & compType)
{
    bool added = false;

    if (!m_componentLock && entity < m_entities.size())
    {
        auto citer = m_compFactory.find(compType);

        if (hasComponent(entity, compType) && citer != m_compFactory.end())
        {
            Component * newComp = m_compFactory[compType]();
            m_entities[entity]->components.push_back(newComp);
            m_entities[entity]->componentMask.setBit((unsigned int)compType);
            
            added = true;
        }
    }
    else
        LOG("Component is locked...");

    return added;
}

bool EntityManager::removeComponent(const unsigned int & entity, const ComponentType & compType)
{
    bool removed = false;

    if (entity < m_entities.size())
    {
        auto ctype_iter = m_compFactory.find(compType);

        if (hasComponent(entity, compType) && ctype_iter != m_compFactory.end())
        {
            Entity * ent = m_entities[entity];

            for (auto citer = ent->components.begin(); 
                 removed == false && citer != ent->components.end(); ++citer)
            {
                if ((*citer)->getType() == compType)
                {
                    delete (*citer);
                    ent->components.erase(citer);
                    removed = true;
                }
            }
        }
    }

    return removed;
}

bool EntityManager::hasComponent(const unsigned int & entity, const ComponentType & compType)
{
    if (entity < m_entities.size())
        return m_entities[entity]->componentMask.getBit((unsigned int)compType);

    return false;
}

void EntityManager::purge()
{
    // SystemManager - Remove all references to the entities
    m_sysManager->clearEntities();

    for (Entity * entity : m_entities)
    {
        for (Component * entityComp : entity->components)
            delete entityComp;

        entity->components.clear();
        delete entity;
    }

    m_entities.clear();
}
