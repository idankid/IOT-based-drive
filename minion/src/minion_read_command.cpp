/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "minion_read_args.hpp"
#include "handleton.hpp"
#include "file_manager.hpp"
#include "minion_read_command.hpp"

std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
ilrd::ReadCommand::Run(std::shared_ptr<ilrd::ITaskArgs> args_)
{
    std::shared_ptr<ilrd::ReadArgs> args = std::static_pointer_cast<ReadArgs>(args_);
 
    std::shared_ptr<char[]> to_fill(new char[args->GetLength()]);

    bool res = ilrd::Handleton<FileManager>::GetInstance()->
                Read(to_fill, args->GetLength(), args->GetOffset());
    
    args->GetProxy()->SendReadResponse(args->GetUid(), res, to_fill, args->GetLength());
    return std::make_pair(nullptr, std::chrono::milliseconds(0));
}
