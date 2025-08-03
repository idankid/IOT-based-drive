/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __FILE_MANAGER_HPP__
#define __FILE_MANAGER_HPP__

#include <mutex>
#include <string>
#include <fstream>
#include "i_file_manger.hpp"

namespace ilrd
{

class FileManager : public IFileManager
{
public:
    FileManager(const std::string& path = "./minion.dat");
    ~FileManager() = default;
    FileManager(const FileManager& other) = delete;
    bool Read(std::shared_ptr<char[]> to_read_to, int64_t len, int64_t offset);
    bool Write(std::shared_ptr<char[]> to_write, int64_t len, int64_t offset);
private:
    std::fstream m_file;
    std::mutex m_lock;
};

}//namespace ilrd

#endif /*__FILE_MANAGER_HPP__*/
