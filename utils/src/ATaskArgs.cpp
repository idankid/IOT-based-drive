/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "ATaskArgs.hpp"

ilrd::ATaskArgs::ATaskArgs(size_t offset, size_t length) : m_uid(ilrd::UID()),
m_offset(offset), m_length(length)
{}

ilrd::UID ilrd::ATaskArgs::GetUid() const
{
    return m_uid;
}

size_t ilrd::ATaskArgs::GetLength()
{
	return m_length;
}

size_t ilrd::ATaskArgs::GetOffset()
{
	return m_offset;
}

void ilrd::ATaskArgs::SetUID(UID id)
{
	m_uid = id;
}

void ilrd::ATaskArgs::SetLength(size_t length)
{
	m_length = length;
}

void ilrd::ATaskArgs::SetOffset(size_t offset)
{
	m_offset = offset;
}
