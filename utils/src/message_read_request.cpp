/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "message_read_request.hpp"

ilrd::MessageReadRequest::MessageReadRequest(UID id, uint64_t offset,
    uint64_t length)
    : AMessageRequest(id, offset, length)
{}

int32_t ilrd::MessageReadRequest::GetClassType() const
{
    return MessageType::READ_REQUEST;
}