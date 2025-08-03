/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __I_RESPONSE_HPP__
#define __I_RESPONSE_HPP__

#include "types.hpp"
#include "ticket.hpp"

namespace ilrd
{

class IResponse
{
public:
    virtual void OnSuccess(TaskResult, Reply) = 0;
    virtual void OnFailure(TaskResult, Reply) = 0;
};

}//namespace ilrd

#endif /*__I_RESPONSE_HPP__*/
