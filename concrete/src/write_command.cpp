/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/
#include <iostream>

#include <cstring>
#include "handleton.hpp"
#include "minion_manager.hpp"
#include "check_functor.hpp"
#include "write_args.hpp"
#include "write_command.hpp"

std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
		ilrd::WriteCommand::Run(std::shared_ptr<ilrd::ITaskArgs> args_)
{
	std::shared_ptr<WriteArgs> args = std::static_pointer_cast<WriteArgs>(args_);
	
	 Handleton<MinionManager>::GetInstance()->AddWriteTask(args);

	return std::make_pair(CheckFunctor(args->GetUid()), std::chrono::milliseconds(500));
}
