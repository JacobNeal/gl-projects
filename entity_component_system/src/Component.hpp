#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <sstream>

#include "Types.hpp"

class Component
{
    public:
        Component(const ComponentType & type);

        ComponentType getType();

        friend std::stringstream & operator >>(std::stringstream & stream, Component & comp)
        {
            comp.read(stream);
            return stream;
        }

        virtual void read(std::stringstream & stream) = 0;

    protected:
        /****************************************
         * Data members
        ****************************************/
        ComponentType m_type;
};

#endif
