/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "message_response.hpp"

ilrd::AMessageResponse::AMessageResponse(ilrd::UID id, bool res) : AMessage(id)
, m_status(res)
{}

char* ilrd::AMessageResponse::Stringify(char* buffer)
{
    buffer = AMessage::Stringify(buffer);
    
    *(bool*)buffer = m_status;
    buffer+= sizeof(bool);

    return buffer;
}

char* ilrd::AMessageResponse::Parse(char* buffer)
{
    buffer = AMessage::Parse(buffer);
    
    this->m_status = *(bool*)buffer;
    buffer += sizeof(bool);
    
    return buffer;
}

int32_t ilrd::AMessageResponse::GetSize()
{
    return AMessage::GetSize() + sizeof(bool);
}

bool ilrd::AMessageResponse::GetStatus() const
{
    return m_status;
}
