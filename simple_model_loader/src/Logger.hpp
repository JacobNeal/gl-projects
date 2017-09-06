#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#define LOGGER_CONTEXT_WIDTH 48

class Logger
{
    public:
        Logger(bool outputLive = false) : m_outputLive(outputLive)
        { }

        void log(std::string logMessage, std::string contextFile="", std::string contextMethod="", int contextLine=-1)
        {
            std::string logContext = contextFile + "(" + std::to_string(contextLine) + ")::" + contextMethod + ":";
            m_logMessages.push_back(logMessage);
            m_logContexts.push_back(logContext);

            if (m_outputLive)
            {
                std::cout << std::left << std::setw(LOGGER_CONTEXT_WIDTH)
                          << logContext << logMessage << '\n';
            }
        }

        friend std::ostream & operator<< (std::ostream & output, const Logger & logger)
        {
            output << "----------------BEGIN LOG OUTPUT----------------\n";

            for (unsigned int count = 0; count < logger.m_logMessages.size(); ++count)
            {
                output << std::left << std::setw(LOGGER_CONTEXT_WIDTH) 
                       << logger.m_logContexts[count] << logger.m_logMessages[count] << '\n';
            }

            output << "-----------------END LOG OUTPUT-----------------\n";

            return output;
        }

    private:
        /****************************************
         * Data members
        ****************************************/
        std::vector<std::string> m_logMessages;
        std::vector<std::string> m_logContexts;
        bool                     m_outputLive;
};

// Create global logger
extern Logger globalLogger;

#define LOG(message) globalLogger.log(message, __FILE__, __func__, __LINE__)
#define LOGGER globalLogger

#define LOGGER_DECL Logger globalLogger;
#define LOGGER_DECL_LIVE Logger globalLogger(true);

#endif
