/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __INPUT_PROXY_HPP__
#define __INPUT_PROXY_HPP__

#include <memory> /* shared_ptr */
#include "types.hpp"

namespace ilrd
{
class ITaskArgs
{
public:
    // @description - returns the key from the factory
    virtual int GetKey() = 0;
};

class IInputProxy
{
public:
    /*
        @description - gets the task arguments
    */
    virtual std::shared_ptr<ilrd::ITaskArgs> GetTaskArgs(int fd, Mode) = 0;
};

}//namespace ilrd

#endif /*__INPUT_PROXY_HPP__*/
