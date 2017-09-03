#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "System.hpp"
#include "Window.hpp"
#include "Logger.hpp"

#include "PositionComp.hpp"
#include "ShapeComp.hpp"

class RenderSystem : public System
{
    public:
        RenderSystem()
            : System(SystemType::Renderer)
        {
            m_requirementMask.setBit((unsigned int)ComponentType::Position);
            m_requirementMask.setBit((unsigned int)ComponentType::Shape);
        }

        void render(Window * window)
        {
            for (Entity * entity : m_entities)
            {
                //PositionComp * positionComp = (PositionComp*)entity->components[(unsigned int)ComponentType::Position];
                ShapeComp * shapeComp = (ShapeComp*)entity->components[(unsigned int)ComponentType::Shape];

                shapeComp->draw(window);
            }
        }

        virtual void update(float deltaTime)
        {
            
        }

        virtual void handleEvent(const EventType & event)
        {
            if (event == EventType::MoveUp ||
                event == EventType::MoveDown ||
                event == EventType::MoveLeft ||
                event == EventType::MoveRight)
            {

            }
        }
};

#endif
