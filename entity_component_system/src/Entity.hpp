#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include "Component.hpp"
#include "Bitmask.hpp"

struct Entity
{
    std::vector<Component *> components;
    Bitmask componentMask;
};

#endif
