/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "file_manager.hpp"

ilrd::FileManager::FileManager(const std::string& path) : 
m_file(path, std::ios::in | std::ios::out)
{}

bool ilrd::FileManager::Read(std::shared_ptr<char[]> to_read_to, int64_t len, int64_t offset)
{
    std::unique_lock<std::mutex> lock(m_lock);
    try
    {
        m_file.seekg(offset);
        m_file.read(to_read_to.get(), len);
    }
    catch(...)
    {
        return false;
    }

    return true;
}

bool ilrd::FileManager::Write(std::shared_ptr<char[]> to_write, int64_t len, int64_t offset)
{
    std::unique_lock<std::mutex> lock(m_lock);
    try
    {
        m_file.seekg(offset);
        m_file.write(to_write.get(), len);
        m_file.flush();
    }
    catch(...)
    {
        return false;
    }
    
    return true;
}