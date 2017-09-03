#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <vector>

#include "Window.hpp"
#include "Types.hpp"
#include "System.hpp"
#include "RenderSystem.hpp"
#include "Entity.hpp"
#include "Bitmask.hpp"
#include "Logger.hpp"

class SystemManager
{
    public:
        SystemManager();
        ~SystemManager();

        void addEntity(Entity * entity);
        void removeEntity(Entity * entity);
        void clearEntities();

        void handleEvent(const EventType & event);

        void render(Window * window);
        void update(float elapsedTime);

    private:
        /****************************************
         * Data members
        ****************************************/
        std::vector<System *>  m_systems;
};

#endif
