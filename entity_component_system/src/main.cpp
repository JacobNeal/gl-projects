#include <iostream>

#include "Window.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "Bitmask.hpp"
#include "Logger.hpp"

#include "PositionComp.hpp"
#include "ShapeComp.hpp"

Logger globalLogger;

int main()
{
    Window window("Entity Component System", 800, 640);

    SystemManager sysManager;
    EntityManager entityManager(&sysManager);

    // Add component types to the entity manager
    entityManager.addComponentType<PositionComp>(ComponentType::Position);
    entityManager.addComponentType<ShapeComp>(ComponentType::Shape);

    Bitmask entityMask;
    entityMask.setBit((unsigned int)ComponentType::Position);
    entityMask.setBit((unsigned int)ComponentType::Shape);

    entityManager.addEntity(entityMask);

    while (!window.isDone())
    {
        window.beginDraw();

        sysManager.update(window.getElapsedTime());
        window.update();

        sysManager.render(&window);

        window.endDraw();
    }

    std::cout << globalLogger;

    return 0;
}
