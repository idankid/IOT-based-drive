/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "minion_write_args.hpp"
#include "handleton.hpp"
#include "file_manager.hpp"
#include "minion_write_command.hpp"

std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
ilrd::WriteCommand::Run(std::shared_ptr<ilrd::ITaskArgs> args_)
{
    std::shared_ptr<ilrd::WriteArgs> args = std::static_pointer_cast<WriteArgs>(args_);
    bool res = ilrd::Handleton<FileManager>::GetInstance()->
                Write(args->GetBuffer(), args->GetLength(), args->GetOffset());
    
    args->GetProxy()->SendWriteResponse(args->GetUid(), res);

    return std::make_pair(nullptr, std::chrono::milliseconds(0));
}
