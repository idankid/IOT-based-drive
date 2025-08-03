/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex Reactor
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include <vector>
#include "types.hpp"

namespace ilrd
{
class IListener
{
public:
    virtual std::vector<std::pair<int, Mode>> 
                        Listen(std::vector<std::pair<int, Mode>>) = 0;
};

}// namsepace ilrd

#endif /*__LISTENER_HPP__*/
