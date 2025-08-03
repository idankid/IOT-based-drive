/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MINION_READ_COMMAN_HPP__
#define __MINION_READ_COMMAN_HPP__


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
		Run(std::shared_ptr<ilrd::ITaskArgs>);
};

}//namespace ilrd

#endif /*__MINION_READ_COMMAN_HPP__*/
