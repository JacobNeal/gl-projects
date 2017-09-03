#include "SystemManager.hpp"

SystemManager::SystemManager()
{
    m_systems.push_back(new RenderSystem());
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
    LOG("Adding entity to systems...");

    for (std::vector<System *>::iterator siter = m_systems.begin();
         siter != m_systems.end(); ++siter)
    {
        if ((*siter)->getRequirements().matches(entity->componentMask))
        {
            unsigned int systemType = (unsigned int)(*siter)->getType();
            LOG("Matches system: " + std::to_string(systemType));
            (*siter)->addEntity(entity);
        }
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

void SystemManager::render(Window * window)
{
    RenderSystem * renderer = (RenderSystem*)m_systems[(unsigned int)SystemType::Renderer];
    renderer->render(window);
}

void SystemManager::update(float elapsedTime)
{
    for (System * system : m_systems)
        system->update(elapsedTime);
}
