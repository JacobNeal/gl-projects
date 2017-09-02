#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include <queue>

class EventQueue
{
    public:
        void addEvent(const unsigned int & eventId);

        bool processEvents(unsigned int & eventId);

        void clearEvents();

    private:
        /****************************************
         * Data members
        ****************************************/
        std::queue<unsigned int>  m_events;
};

#endif
