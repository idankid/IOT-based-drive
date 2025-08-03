/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "handleton.hpp"
#include "minion_manager.hpp"
#include "check_functor.hpp"
#include "read_args.hpp"
#include "read_command.hpp"

std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
		ilrd::ReadCommand::Run(std::shared_ptr<ilrd::ITaskArgs> args_)
{
	std::shared_ptr<ReadArgs> args = std::static_pointer_cast<ReadArgs>(args_);
	
	Handleton<MinionManager>::GetInstance()->AddReadTask(args);

	return std::make_pair(CheckFunctor(args->GetUid()),  std::chrono::milliseconds(500));
}
