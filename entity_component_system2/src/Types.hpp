#ifndef TYPES_HPP
#define TYPES_HPP

#define NUM_COMPONENT_TYPES 32

enum class ComponentType
{
    Position, Movable, Controller
};

enum class SystemType
{
    Renderer, Movement, Control, State
};

enum class EventType
{
    MoveUp, MoveDown, MoveLeft, MoveRight
};

#endif
