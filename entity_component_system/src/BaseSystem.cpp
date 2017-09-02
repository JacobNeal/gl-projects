#include "BaseSystem.hpp"

BaseSystem::BaseSystem(const System & system, SystemManager * sysManager)
    : m_system(system), m_sysManager(sysManager)
{ }

BaseSystem::~BaseSystem()
{
    purge();
}

bool BaseSystem::addEntity(const unsigned int & entity)
{
    if (hasEntity(entity))
        return false;

    m_entities.emplace_back(entity);
    return true;
}

bool BaseSystem::hasEntity(const unsigned int & entity)
{
    return m_entities.find(entity) != m_entities.end();
}

bool BaseSystem::removeEntity(const unsigned int & entity)
{
    std::vector<unsigned int>::iterator iter = m_entities.find(entity);

    if (iter == m_entities.end())
        return false;

    m_entities.erase(entity);
    return true;
}

bool BaseSystem::fitsRequirements(const std::bitset<NUM_COMPONENT_TYPES> & bits)
{

}
