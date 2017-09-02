#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <pair>
#include <vector>
#include <bitset>
#include <string>

#include "Types.hpp"
#include "BaseComp.hpp"

#define ComponentContainer std::vector<BaseComp *>
#define EntityData std::pair<std::bitset<NUM_COMPONENT_TYPES>, ComponentContainer>
#define EntityContainer std::unordered_map<unsigned int, EntityData>
#define ComponentFactory std::unordered_map<Component, std::function<BaseComp*(void)>>

class EntityManager
{
    public:
        EntityManager();

        unsigned int addEntity(const std::bitset<NUM_COMPONENT_TYPES> & mask);
        unsigned int addEntity(const std::string & entityFile);
        bool removeEntity(const unsigned int & entity);
        
        bool addComponent(const unsigned int & entity, const Component & compType);
        bool removeComponent(const unsigned int & entity, const Component & compType);
        bool hasComponent(const unsigned int & entity, const Component & compType);

        template <typename T>
        T * getComponent(const unsigned int & entity, const Component & compType)
        {
            EntityContainer::iterator iter = m_entities.find(entity);
            T * component = nullptr;

            if (iter != m_entities.end())
            {
                // Check if the component exists using the bitset
                if (iter->second.first[(unsigned int)compType])
                {
                    ComponentContainer & container = iter->second.second;
                    
                    for (ComponentContainer::iterator citer = container.begin();
                         component == nullptr && citer != container.end(); ++citer)
                    {
                        if (citer->getType() == compType)
                            component = citer; 
                    }
                }
            }

            return component;
        }

        void purge();

    private:
        /****************************************
         * Data members
        ****************************************/
        EntityContainer   m_entities;
        ComponentFactory  m_factory;
        unsigned int      m_numEntities;
};

#endif
