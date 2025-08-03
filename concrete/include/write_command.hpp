/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __WRITE_COMMAND_HPP__
#define __WRITE_COMMAND_HPP__

#include <chrono>
#include <functional>
#include <memory>

#include "input_proxy.hpp"
#include "command.hpp"

namespace ilrd
{
class WriteCommand : public ilrd::ICommand
{
public:
	std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
		Run(std::shared_ptr<ilrd::ITaskArgs>);
};


}//namespace ilrd

#endif /*__WRITE_COMMAND_HPP__*/
