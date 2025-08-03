/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __I_MINION_PROXY_HPP__
#define __I_MINION_PROXY_HPP__

#include <memory>

#include "types.hpp"
#include "Dispastcher.hpp"
#include "AMessage.hpp"

namespace ilrd
{
class IMinionProxy
{
public:
    virtual void AddWriteTask(UID id, size_t offset, size_t length, 
                            std::shared_ptr<char[]> data) = 0;
    virtual void AddReadTask(UID id, size_t offset, size_t length) = 0;
        
    virtual int GetMinionFD() = 0;

    virtual void OnMinionWake(int fd, Mode mode) = 0;
};

}//namespace ilrd

#endif /*__I_MINION_PROXY_HPP__*/
