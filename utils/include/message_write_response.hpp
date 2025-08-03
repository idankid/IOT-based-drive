/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_WRITE_RESPONSE_HPP__
#define __MESSAGE_WRITE_RESPONSE_HPP__

#include "message_response.hpp"

namespace ilrd
{

class MessageWriteResponse : public AMessageResponse
{
public:
    MessageWriteResponse() = default;
    MessageWriteResponse(UID id, bool status);
    int32_t GetClassType() const;
};

}//namespace ilrd

#endif /*__MESSAGE_WRITE_RESPONSE_HPP__*/
