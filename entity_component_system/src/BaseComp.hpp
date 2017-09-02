#ifndef BASE_COMP_HPP
#define BASE_COMP_HPP

#include <sstream>

#include "Types.hpp"

class BaseComp
{
    public:
        BaseComp(const Component & type);

        Component getType();

        friend std::stringstream & operator >>(std::stringstream & stream, BaseComp & comp)
        {
            comp.read(stream);
            return stream;
        }

        virtual void read(std::stringstream & stream) = 0;

    protected:
        /****************************************
         * Data members
        ****************************************/
        Component m_type;
};

#endif
