#ifndef TYPES_HPP
#define TYPES_HPP

#define NUM_COMPONENT_TYPES 32

enum class Component
{
    Position=0, Movable, Controller
};

enum class System
{
    Renderer=0, Movement, Control, State
};

enum class EntityEvent
{
    Moving_Up, Moving_Down, Moving_Left, Moving_Right
};

#endif
