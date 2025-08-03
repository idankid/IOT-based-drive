/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __I_FILE_MANAGER_HPP__
#define __I_FILE_MANAGER_HPP__

#include <memory>

namespace ilrd
{

class IFileManager
{
public:
    virtual bool Read(std::shared_ptr<char[]> to_read_to, int64_t len, 
                                                            int64_t offset) = 0;
    virtual bool Write(std::shared_ptr<char[]> to_write, int64_t len,
                                                            int64_t offset) = 0;
    virtual ~IFileManager() = default;
};

}//namespace ilrd

#endif //__I_FILE_MANAGER_HPP__