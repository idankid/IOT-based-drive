/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-09
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "cstring"
#include "message_write_request.hpp"

ilrd::MessageWriteRequest::MessageWriteRequest(UID id, uint64_t offset,
    uint64_t length, std::shared_ptr<char[]> buffer)
    : AMessageRequest(id, offset, length), m_buffer(buffer)
{}

int32_t ilrd::MessageWriteRequest::GetClassType() const
{
    return MessageType::WRITE_REQUEST;
}

int32_t ilrd::MessageWriteRequest::GetSize()
{
    return AMessageRequest::GetSize() + this->m_length;
}

char* ilrd::MessageWriteRequest::Stringify(char* buffer)
{
    buffer = AMessageRequest::Stringify(buffer);

    memcpy(buffer, m_buffer.get(), m_length);
    buffer += m_length;

    return buffer;
}

char* ilrd::MessageWriteRequest::Parse(char* buffer)
{
    buffer = AMessageRequest::Parse(buffer);
    std::shared_ptr<char[]>temp(new char[this->m_length]);
    m_buffer = temp; 
    memcpy(m_buffer.get(), buffer, m_length);
    buffer += m_length;

    return buffer;
}

std::shared_ptr<char[]> ilrd::MessageWriteRequest::GetBuffer()
{
    return m_buffer;
}
