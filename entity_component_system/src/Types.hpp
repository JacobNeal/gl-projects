#ifndef TYPES_HPP
#define TYPES_HPP

#define NUM_COMPONENT_TYPES 32

enum class ComponentType
{
    Position=0, Shape, Transformable, Controller
};

enum class SystemType
{
    Renderer=0, Movement, Control, State
};

enum class EventType
{
    MoveUp=0, MoveDown, MoveLeft, MoveRight
};

#endif
