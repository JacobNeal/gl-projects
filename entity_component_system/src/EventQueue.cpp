#include "EventQueue.hpp"

void EventQueue::addEvent(const unsigned int & eventId)
{
    m_events.push(eventId);
}

bool EventQueue::processEvents(unsigned int & eventId)
{
    if (m_events.empty())
        return false;

    eventId = m_events.front();
    m_events.pop();

    return true;
}

void EventQueue::clearEvents()
{
    while (!m_events.empty())
        m_events.pop();
}
