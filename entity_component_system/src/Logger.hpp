#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <vector>
#include <string>

class Logger
{
    public:
        void log(std::string message)
        {
            m_logMessages.push_back(message);
        }

        friend std::ostream & operator<< (std::ostream & output, const Logger & logger)
        {
            for (std::string message : logger.m_logMessages)
                output << message << '\n';

            return output;
        }

    private:
        /****************************************
         * Data members
        ****************************************/
        std::vector<std::string> m_logMessages;
};

// Create global logger
extern Logger globalLogger;

#define LOG(message) globalLogger.log(message)

#endif
