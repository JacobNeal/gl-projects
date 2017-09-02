#include "SystemManager.hpp"

SystemManager::SystemManager()
{
    //m_systems.push_back(new RenderSystem());
}

SystemManager::~SystemManager()
{
    while (m_systems.begin() != m_systems.end())
    {
        delete (*m_systems.begin());
        m_systems.erase(m_systems.begin());
    }
}

void SystemManager::addEntity(Entity * entity)
{
    for (std::vector<System *>::iterator siter = m_systems.begin();
         siter != m_systems.end(); ++siter)
    {
        if ((*siter)->getRequirements().matches(entity->componentMask))
            (*siter)->addEntity(entity);
    }
}

void SystemManager::removeEntity(Entity * entity)
{
    for (std::vector<System *>::iterator siter = m_systems.begin();
         siter != m_systems.end(); ++siter)
    {
        (*siter)->removeEntity(entity);
    }
}

void SystemManager::clearEntities()
{
    for (auto siter = m_systems.begin(); siter != m_systems.end(); ++siter)
    {
        (*siter)->clearEntities();
    }
}

void SystemManager::handleEvent(const EventType & event)
{
    for (std::vector<System *>::iterator siter = m_systems.begin();
         siter != m_systems.end(); ++siter)
    {
        (*siter)->handleEvent(event);
    }
}
