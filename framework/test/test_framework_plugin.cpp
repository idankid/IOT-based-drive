/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-30
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <chrono>
#include <functional>
#include <iostream>

#include "handleton.hpp"
#include "factory.hpp"
#include "command.hpp"
#include "Listener.hpp"


class PluginReadArgs : public ilrd::ITaskArgs
{
public:
	PluginReadArgs(int fd, size_t offset = 0, size_t length = 0);
	PluginReadArgs(const PluginReadArgs& other) = delete;
	~PluginReadArgs() = default;
	int GetKey();
	size_t GetLength();
	size_t GetOffset();
	void SetLength(size_t length);
	void SetOffset(size_t offset);
	int m_fd;
private:
	size_t m_offset;
	size_t m_length;
};

PluginReadArgs::PluginReadArgs(int fd, size_t offset, size_t length): m_fd(fd),
 m_offset(offset), m_length(length) 
{}

size_t PluginReadArgs::GetLength()
{
	return m_length;
}

size_t PluginReadArgs::GetOffset()
{
	return m_offset;
}

void PluginReadArgs::SetLength(size_t length)
{
	m_length = length;
}

void PluginReadArgs::SetOffset(size_t offset)
{
	m_offset = offset;
}

int PluginReadArgs::GetKey()
{
	return (int)ilrd::IListener::READ;
}

class ReadCommand : public ilrd::ICommand
{
public:
	std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
		Run(std::shared_ptr<ilrd::ITaskArgs>);
};

std::pair<std::function<bool(void)>, std::chrono::milliseconds> 
		ReadCommand::Run(std::shared_ptr<ilrd::ITaskArgs> args_)
{
	(void)args_;
	std::cout << "plugin read Command" << std::endl;
	throw std::runtime_error("hello");
	return std::make_pair(nullptr,  std::chrono::milliseconds(0));
}


std::shared_ptr<ilrd::ICommand> CreateNewReadCommand()
{
	return std::shared_ptr<ilrd::ICommand>(new ReadCommand);
}

__attribute__((constructor)) static void loaded()
{
    ilrd::Handleton<ilrd::Factory<int, ilrd::ICommand>>::GetInstance()->
        Register(ilrd::Mode::READ, CreateNewReadCommand);
}