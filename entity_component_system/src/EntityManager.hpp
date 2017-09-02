#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

#include "Types.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "Bitmask.hpp"
#include "SystemManager.hpp"
#include "Logger.hpp"

class EntityManager
{
    public:
        EntityManager(SystemManager * sysManager);
        ~EntityManager();

        void addEntity(Bitmask mask);
        void addEntity(const std::string & entityFile);
        bool removeEntity(const unsigned int & entity);

        bool addComponent(const unsigned int & entity, const ComponentType & compType);
        bool removeComponent(const unsigned int & entity, const ComponentType & compType);
        bool hasComponent(const unsigned int & entity, const ComponentType & compType);

        void purge();

        template <typename T>
        void addComponentType(const ComponentType & type)
        {
            m_compFactory[type] = []()->Component* { return new T(); };
        }

    private:
        /*******************************************
         * Data members
        *******************************************/
        std::unordered_map<ComponentType, std::function<Component*(void)>> m_compFactory;
        std::vector<Entity *> m_entities; 
        SystemManager * m_sysManager;
        bool m_componentLock;
};

#endif
