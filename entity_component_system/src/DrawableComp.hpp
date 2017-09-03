#ifndef DRAWABLE_COMP_HPP
#define DRAWABLE_COMP_HPP

#include "Component.hpp"
#include "Window.hpp"

class DrawableComp : public Component
{
    public:
        DrawableComp(const ComponentType & compType)
            : Component(compType)
        { }

        virtual void draw(Window * window) = 0;
};

#endif
