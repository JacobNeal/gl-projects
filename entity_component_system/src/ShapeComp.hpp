#ifndef SHAPE_COMP_HPP
#define SHAPE_COMP_HPP

#include "DrawableComp.hpp"
#include "Triangle.hpp"
#include "Window.hpp"

class ShapeComp : public DrawableComp
{
    public:
        ShapeComp()
            : DrawableComp(ComponentType::Shape)
        { }

        virtual void draw(Window * window)
        {
            window->draw(&m_shape);
        }

        virtual void read(std::stringstream & stream)
        {
            GLfloat size;
            stream >> size;
            m_shape.setSize(size);
        }

    private:
        /****************************************
         * Data members
        ****************************************/
        Triangle m_shape;
};

#endif
