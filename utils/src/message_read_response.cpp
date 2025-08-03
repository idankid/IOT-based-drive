/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-10
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "cstring"
#include "message_read_response.hpp"

ilrd::MessageReadResponse::MessageReadResponse(UID id,
                    bool status, std::shared_ptr<char[]> res, int64_t res_len)
: AMessageResponse(id, status), m_res(res), m_len(res_len)
{}

int32_t ilrd::MessageReadResponse::GetClassType() const
{
    return MessageType::READ_RESPONSE;
}

int32_t ilrd::MessageReadResponse::GetSize()
{
    return AMessageResponse::GetSize() + sizeof(int64_t) + m_len;
}


char* ilrd::MessageReadResponse::Stringify(char* buffer)
{
    buffer = AMessageResponse::Stringify(buffer);

    *(int64_t*)buffer = m_len;
    buffer += sizeof(int64_t);
    
    memcpy(buffer, m_res.get(), m_len);
    buffer += m_len;

    return buffer;
}


char* ilrd::MessageReadResponse::Parse(char* buffer)
{
    buffer = AMessageResponse::Parse(buffer);

    m_len = *(int64_t*)buffer;
    buffer += sizeof(int64_t);
    
    std::shared_ptr<char[]>temp(new char[m_len]);
    m_res = temp; 
    memcpy(m_res.get(), buffer, m_len);
    buffer += m_len;

    return buffer;
}

std::shared_ptr<char[]> ilrd::MessageReadResponse::GetData() const
{
    return m_res;
}

int64_t ilrd::MessageReadResponse::GetDataLen() const
{
    return m_len;
}