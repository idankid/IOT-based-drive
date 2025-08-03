/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-22
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __WRITE_RESPONSE_HPP__
#define __WRITE_RESPONSE_HPP__

#include "i_response.hpp"

namespace ilrd
{
class WriteResponse : public IResponse
{
public:
    void OnSuccess(TaskResult, Reply);
    void OnFailure(TaskResult, Reply);
};

}//namespace ilrd

#endif /*__WRITE_RESPONSE_HPP__*/
