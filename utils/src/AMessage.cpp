/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <memory>

#include "AMessage.hpp"

ilrd::AMessage::AMessage(ilrd::UID id) : m_uid(id)
{}

char* ilrd::AMessage::Stringify(char* buffer)
{
        *(int32_t*)buffer = this->GetSize();
        buffer+= sizeof(int32_t);
        
        *(int32_t*)buffer = this->GetClassType();
        buffer+= sizeof(int32_t);
        
        buffer = m_uid.Stringify(buffer);
        
        return buffer;
}

char* ilrd::AMessage::Parse(char* buffer)
{
        return m_uid.Parse(buffer);
}

int32_t ilrd::AMessage::GetSize()
{
        return m_uid.GetSize() + sizeof(int32_t) * 2;
}

ilrd::UID ilrd::AMessage::GetUID()
{
        return m_uid;
}