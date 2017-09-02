#include <iostream>

#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include "PositionComp.hpp"
#include "Bitmask.hpp"

int main()
{
    SystemManager sysManager;
    EntityManager entityManager(&sysManager);

    entityManager.addComponentType<PositionComp>(ComponentType::Position);
    entityManager.addEntity(Bitmask(0));

    std::cout << "End of main...\n";

    return 0;
}
