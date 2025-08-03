/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil		 	 				
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
#include "write_args.hpp"
#include "write_command.hpp"
#include "read_args.hpp"
#include "read_command.hpp"
#include "minion_proxy.hpp"
#include "handleton.hpp"
#include "minion_manager.hpp"

#include "framework.hpp"


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

int main()
{
	InitMessages();
	ilrd::Handleton<ilrd::ResponseManager>::GetInstance();//to init the response manager
	std::vector<std::shared_ptr<ilrd::IMinionProxy>> minions;
	minions.push_back(std::shared_ptr<ilrd::IMinionProxy>(new ilrd::MinionProxy("192.168.239.128", 12345)));
	ilrd::Handleton<ilrd::MinionManager>::GetInstance()->Init(minions);
	ilrd::NBDProxy nbd_proxy;
	std::vector<ilrd::Framework::CallbackListItem> input_proxies;
	input_proxies.push_back({STDIN_FILENO,ilrd::Mode::READ ,&nbd_proxy});
	std::vector<ilrd::Framework::FactoryListItem> creators; 
	creators.push_back({ilrd::Mode::READ,CreateReadCommand});
	creators.push_back({ilrd::Mode::Write,CreateWriteCommand});
	
		
	ilrd::Framework fw(input_proxies,"./plugins",creators);
	fw.Run();
	  
	return 0;
}
