/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-22
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __READ_RESPONSE_HPP__
#define __READ_RESPONSE_HPP__

#include "i_response.hpp"

namespace ilrd
{

class ReadResponse : public IResponse
{
public:
    void OnSuccess(TaskResult, Reply);
    void OnFailure(TaskResult, Reply);
};

}//namespace ilrd

#endif /*__READ_RESPONSE_HPP__*/
