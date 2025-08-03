/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <vector>
#include <iostream>

#include "handleton.hpp"
#include "factory.hpp"
#include "types.hpp"
#include "framework.hpp"
#include "master_proxy.hpp"
#include "minion_read_command.hpp"
#include "minion_write_command.hpp"

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        std::cout << "missing binding port" << std::endl;
        return 1;
    }
    ilrd::MasterProxy prox(atoi(argv[1]));

    std::vector<ilrd::Framework::CallbackListItem> callbacks;
    callbacks.push_back({prox.GetFd(), ilrd::Mode::READ, &prox});
    callbacks.push_back({prox.GetFd(), ilrd::Mode::Write, &prox});

    std::vector<ilrd::Framework::FactoryListItem> commands;
    commands.push_back({ilrd::Mode::READ,
    [](){
        return std::shared_ptr<ilrd::ICommand>(new ilrd::ReadCommand);
    }});
    
	commands.push_back({ilrd::Mode::Write,   
    [](){
        return std::shared_ptr<ilrd::ICommand>(new ilrd::WriteCommand);
    }});

    ilrd::Framework fw(callbacks,"./plugins",commands);
	fw.Run();

    return 0;
}