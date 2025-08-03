/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __LINUX_LISTENER_HPP__
#define __LINUX_LISTENER_HPP__

#include "Listener.hpp"

namespace ilrd
{
class LinuxListener : public IListener
{
    std::vector<std::pair<int, ilrd::Mode>> 
        Listen(std::vector<std::pair<int, ilrd::Mode>>);

};
} // namespace ilrd


#endif /*__LINUX_LISTENER_HPP__*/
