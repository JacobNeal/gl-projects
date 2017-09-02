#ifndef BASE_SYSTEM_HPP
#define BASE_SYSTEM_HPP

#include "Types.hpp"
#include "SystemManager.hpp"

#include <vector>
#include <bitset>

class BaseSystem
{
    public:
        BaseSystem(const System & system, SystemManager * sysManager);
        ~BaseSystem();

        bool addEntity(const unsigned int & entity);
        bool hasEntity(const unsigned int & entity);
        bool removeEntity(const unsigned int & entity);
        bool fitsRequirements(const std::bitset<NUM_COMPONENT_TYPES> & bits);

        System getId();

        void purge();

        virtual void update(float deltaTime) = 0;
        virtual void handleEvent(const unsigned int & entity, const EntityEvent & evt) = 0;

    protected:
        /*****************************************
         * Data members
        *****************************************/
        System                                         m_system;
        std::vector<unsigned int>                      m_entities;
        std::vector<std::bitset<NUM_COMPONENT_TYPES>>  m_requirements;

        SystemManager *                                m_sysManager;
};

#endif
