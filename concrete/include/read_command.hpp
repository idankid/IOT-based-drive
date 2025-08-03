/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __READ_COMMAND_HPP__
#define __READ_COMMAND_HPP__

#include <chrono>
#include <functional>
#include <memory>

#include "input_proxy.hpp"
#include "command.hpp"

namespace ilrd
{
class ReadCommand : public ICommand
{
public:
    std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
        Run(std::shared_ptr<ITaskArgs>);
};
}//namespace ilrd

#endif /*__READ_COMMAND_HPP__*/
