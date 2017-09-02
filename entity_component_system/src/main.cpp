#include <iostream>

#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "PositionComp.hpp"
#include "Bitmask.hpp"
#include "Logger.hpp"

Logger globalLogger;

int main()
{
    SystemManager sysManager;
    EntityManager entityManager(&sysManager);

    entityManager.addComponentType<PositionComp>(ComponentType::Position);

    Bitmask entityMask;
    entityMask.setBit(0);

    entityManager.addEntity(entityMask);

    LOG("End of main...\n");

    std::cout << "----------------BEGIN LOG OUTPUT----------------\n" << globalLogger
              << "-----------------END LOG OUTPUT-----------------\n";

    return 0;
}
