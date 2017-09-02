#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <vector>

#include "Types.hpp"
#include "System.hpp"
#include "Entity.hpp"
#include "Bitmask.hpp"

class SystemManager
{
    public:
        SystemManager();
        ~SystemManager();

        void addEntity(Entity * entity);
        void removeEntity(Entity * entity);
        void clearEntities();

        void handleEvent(const EventType & event);

    private:
        /****************************************
         * Data members
        ****************************************/
        std::vector<System *>  m_systems;
};

#endif
