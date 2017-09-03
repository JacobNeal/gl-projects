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
    LOG("Adding new entity...");

    std::string logMessage = "Added new entity with bitmask: ";
    char logBitmask[NUM_COMPONENT_TYPES + 1] = {'\0'};

    Entity * entity = new Entity;
    m_entities.push_back(entity);

    for (unsigned int bit = 0; bit < NUM_COMPONENT_TYPES; ++bit)
    {
        bool bitSet = mask.getBit(bit);

        if (bitSet)
        {
            auto citer = m_compFactory.find((ComponentType)bit);
            
            if (citer != m_compFactory.end())
            {                    
                Component * newComp = citer->second();
                entity->components.push_back(newComp);
                entity->componentMask.setBit(bit);
            }
            else
                LOG("Can't determine how to instantiate ComponentType: " + std::to_string(bit));

            logBitmask[NUM_COMPONENT_TYPES - bit - 1] = '1';
        }
        else
            logBitmask[NUM_COMPONENT_TYPES - bit - 1] = '0';
    }

    m_sysManager->addEntity(m_entities.back());
    m_componentLock = true;

    LOG(logMessage + logBitmask);
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

        if (!hasComponent(entity, compType) && citer != m_compFactory.end())
        {
            Component * newComp = m_compFactory[compType]();
            m_entities[entity]->components.push_back(newComp);
            m_entities[entity]->componentMask.setBit((unsigned int)compType);
            
            added = true;
        }
    }
    else
        LOG("Adding components is locked since entities have been added.");

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
