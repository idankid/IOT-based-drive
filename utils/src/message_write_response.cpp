/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "message_write_response.hpp"

ilrd::MessageWriteResponse::MessageWriteResponse(ilrd::UID id, bool status)
:AMessageResponse(id, status)
{}

int32_t ilrd::MessageWriteResponse::GetClassType() const
{
    return MessageType::WRITE_RESPOSE;
}