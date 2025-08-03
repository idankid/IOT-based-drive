/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer Ofir Nachshoni		 	 				
************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <ctime>    
#include <fstream>
#include <string>
#include "waitable_queue.hpp"

namespace ilrd
{

class  Logger
{
public:
    enum Level
    {
        EXIT = -1,
        INFO = 0,
        WARNING = 1,
        ERROR = 2
    };

    Logger(const std::string& path = "./logger.txt");
    ~ Logger();
    void Log(const std::string& message, Level level = Level::INFO);
private:
    std::ofstream m_logger;
    std::thread m_thread;

    std::string m_levels[3];

    struct LogMessage
    {
        std::string m_message;
        Level m_level;
        std::time_t m_timestamp;
    };
    WaitableQueue<Logger::LogMessage> m_to_log;

    void ThreadJob();
};

} //namespace ilrd

#endif /*__LOGGER_H__*/
