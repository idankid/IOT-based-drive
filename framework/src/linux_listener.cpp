/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <algorithm> /* for_each */
#include "linux_listener.hpp"

std::vector<std::pair<int, ilrd::Mode>> ilrd::LinuxListener::Listen
    (std::vector<std::pair<int, ilrd::Mode>> to_listen)
{
    fd_set read_fds;
    fd_set write_fds;
    int max = 0;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);

    for(auto& curr : to_listen)
    {
        FD_SET(curr.first, 
         curr.second == Mode::READ ? &read_fds : &write_fds);           
        
        if(curr.first > max)
        {
            max = curr.first;
        }
    }

    int res = select(max + 1, &read_fds, &write_fds, nullptr, nullptr);
    if(res < 0)
    {
        throw std::runtime_error("select failed");
    }
    
    std::vector<std::pair<int, Mode>> return_val;

    for(auto curr : to_listen)
    {
        if(FD_ISSET(curr.first, 
            curr.second == Mode::READ ? &read_fds : &write_fds))
        {
            return_val.push_back(curr);
        }               
    }

    return return_val;
}