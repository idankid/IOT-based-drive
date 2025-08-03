/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MESSAGE_READ_REQUEST_HPP__
#define __MESSAGE_READ_REQUEST_HPP__

#include "memory"
#include "message_request.hpp"

namespace ilrd
{
class MessageReadRequest : public AMessageRequest
{
public:
    MessageReadRequest() = default;
    MessageReadRequest(UID id, uint64_t offset, uint64_t length);
    int32_t GetClassType() const;
};

}//namespace ilrd

#endif /*__MESSAGE_READ_REQUEST_HPP__*/
