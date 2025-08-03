/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex Reactor
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <unistd.h>

#include "UDPSocket.hpp"
#include "linux_listener.hpp"
#include "Reactor.hpp"

void SocketFunc(int fd, ilrd::Mode mode)
{
	char buff[50];
	if(mode == ilrd::Mode::READ)
	{
		read(fd, buff, 50);
		std::cout << "read from " << fd << " " << buff << std::endl;
	}
	else
	{
		std::cout << "write from" << fd << std::endl;
	}
}

int main()
{
	ilrd::UDPSocket socket;
	ilrd::UDPSocket stop_socket;
	ilrd::Reactor react(std::shared_ptr<ilrd::IListener>(new ilrd::LinuxListener()));
	
	socket.bind(12345);
	stop_socket.bind(12346);

	react.Register(socket.GetFD(), ilrd::Mode::Write, SocketFunc);
	react.Register(socket.GetFD(), ilrd::Mode::READ, SocketFunc);
	react.Register(stop_socket.GetFD(), ilrd::Mode::READ, 
		[&react](int fd, ilrd::Mode mode)
	{
		(void)fd;
		(void) mode;
		react.Stop();
	});

	react.Run();
	return 0;
}
