/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-17
* \ <_. )	@Ex 
*  `---' 	@reviewer Ofir Nachshoni 	 				
************************************************/

#include <thread>

#include "logger.hpp"

namespace ilrd
{

Logger::Logger(const std::string& path) : m_logger(path, std::ios::app),
 m_thread(&ilrd::Logger::ThreadJob, this), m_levels{"INFO", "WARNING", "ERROR"}
{}

Logger::~Logger()
{
    try
    {
        this->Log("exit", EXIT);
        m_thread.join();
    }
    catch(...)
    {
    }
    
}

void Logger::ThreadJob()
{
    while(true)
    {
        LogMessage msg;
        m_to_log.Pop(msg);

        if(msg.m_level == EXIT)
        {
            break;
        }

        m_logger << ctime(&msg.m_timestamp) << " " <<
        m_levels[static_cast<int>(msg.m_level)] << " " 
        << msg.m_message << std::endl;
    }
}

void Logger::Log(const std::string& message, Level level)
{
    LogMessage msg;
    msg.m_level = level;
    msg.m_message = message;
    time(&msg.m_timestamp);

    m_to_log.Push(msg);
}

}