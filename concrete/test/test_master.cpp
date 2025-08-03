/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <string>
#include <list> 
#include <cstdlib>

#include "AMessage.hpp"
#include "message_read_response.hpp"
#include "message_write_response.hpp"
#include "response_manager.hpp"
#include "factory.hpp"
#include "NBD_proxy.hpp"
#include "NBD.hpp"
#include "write_args.hpp"
#include "write_command.hpp"
#include "read_args.hpp"
#include "read_command.hpp"
#include "minion_proxy.hpp"
#include "handleton.hpp"
#include "minion_manager.hpp"

#include "framework.hpp"

#define MB (1024 * 1024)

std::shared_ptr<ilrd::ICommand> CreateReadCommand()
{
	return std::shared_ptr<ilrd::ICommand>(new ilrd::ReadCommand);
}

std::shared_ptr<ilrd::ICommand> CreateWriteCommand()
{
	return std::shared_ptr<ilrd::ICommand>(new ilrd::WriteCommand);
}

void InitMessages()
{
	ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
	Register(ilrd::MessageType::READ_RESPONSE, []()
	{
		return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageReadResponse());
	});
	ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::GetInstance()->
	Register(ilrd::MessageType::WRITE_RESPOSE, []()
	{
		return std::shared_ptr<ilrd::AMessage>(new ilrd::MessageWriteResponse());
	});
}

int InitMinions(int argc, char* argv[])
{
	if(argc < 4)
	{
		std::cout << "no minions" << std::endl;
		return -1;
	}

	for(int i = 2; i < argc; i += 2)
	{
		if(i + 1 >= argc)
		{
			std::cout << "missing port for current minion" << std::endl; 
			return -1;
		}
		std::vector<std::shared_ptr<ilrd::IMinionProxy>> minions;
		minions.push_back(std::shared_ptr<ilrd::IMinionProxy>(new ilrd::MinionProxy(argv[i], atoi(argv[i+1]))));
		ilrd::Handleton<ilrd::MinionManager>::GetInstance()->Init(minions);
	}

	return 0;
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "missing device file" << std::endl;
        return 1;
    }

	InitMessages();
    if(InitMinions(argc, argv) == -1)
	{
		return 1;
	}

    //to init the response manager
	ilrd::Handleton<ilrd::ResponseManager>::GetInstance();
	
    ilrd::NBDProxy nbd_proxy;
	std::vector<ilrd::Framework::CallbackListItem> input_proxies;
	input_proxies.push_back({ilrd::NBD::Init(argv[1], 4*MB), ilrd::Mode::READ ,&nbd_proxy});

	std::vector<ilrd::Framework::FactoryListItem> creators; 
	creators.push_back({ilrd::Mode::READ,CreateReadCommand});
	creators.push_back({ilrd::Mode::Write,CreateWriteCommand});
	
	ilrd::Framework fw(input_proxies,"./plugins",creators);
	fw.Run();
	  
	return 0;
}
