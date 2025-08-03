/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-27
* \ <_. )	@Ex framework
*  `---' 	@reviewer Gil	 	 				
************************************************/

#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <functional>   /* function */
#include <chrono>       /*miliseconds*/
#include "input_proxy.hpp"

namespace ilrd
{

class ICommand
{
public:
    /*
        @descricption the function to run on event
        @param args_ - the arguments for the function
        @returns a pair of a function where it returns false to
         run again and true to stop and the interval to run the function 
            if exists
    */
    virtual std::pair<std::function<bool(void)>, std::chrono::milliseconds>
                Run(std::shared_ptr<ITaskArgs> args_) = 0;
};

}//namespace ilrd

#endif /*__COMMAND_HPP__*/
