/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "message_request.hpp"

ilrd::AMessageRequest::AMessageRequest(ilrd::UID id,uint64_t offset, uint64_t length)
: AMessage(id), m_offset(offset), m_length(length)
{}

char* ilrd::AMessageRequest::Stringify(char* buffer)
{
    buffer = AMessage::Stringify(buffer);
    
    *(u_int64_t*)buffer = m_offset;
    buffer+= sizeof(uint64_t);
    
    *(u_int64_t*)buffer = m_length;
    buffer+= sizeof(uint64_t);

    return buffer;
}

char* ilrd::AMessageRequest::Parse(char* buffer)
{
    buffer = AMessage::Parse(buffer);
    
    this->m_offset = *(int64_t*)buffer;
    buffer += sizeof(int64_t);
    
    this->m_length = *(int64_t*)buffer;
    buffer += sizeof(int64_t);

    return buffer;
}

int32_t ilrd::AMessageRequest::GetSize()
{
    return AMessage::GetSize() + sizeof(u_int64_t) * 2;
}

uint64_t ilrd::AMessageRequest::GetLength()
{
    return m_length;
}

uint64_t ilrd::AMessageRequest::GetOffset()
{
    return m_offset;
}