#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <bitset>
#include <vector>

#include "Types.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "Bitmask.hpp"

class System
{
    public:
        System(const SystemType & type);
        virtual ~System();

        bool addEntity(Entity * entity);
        bool removeEntity(Entity * entity);
        bool hasEntity(Entity * entity);
        void clearEntities();

        Bitmask getRequirements();
        SystemType getType();

        virtual void update(float deltaTime) = 0;
        virtual void handleEvent(const EventType & event) = 0;

    protected:
        /****************************************
         * Data members
        ****************************************/
        SystemType                        m_type;
        std::vector<Entity *>             m_entities;
        Bitmask                           m_requirementMask;
};

#endif
