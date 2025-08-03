/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "minion_write_args.hpp"

ilrd::WriteArgs::WriteArgs(size_t offset, size_t length): ATaskArgs(offset, length)
{}

ilrd::WriteArgs::~WriteArgs()
{}

std::shared_ptr<char[]>& ilrd::WriteArgs::GetBuffer()
{
	return m_buffer;
}

void ilrd::WriteArgs::SetBuffer(std::shared_ptr<char[]> buffer)
{
	m_buffer = buffer;
}

int ilrd::WriteArgs::GetKey()
{
	return (int)ilrd::Write;
}

ilrd::MasterProxy* ilrd::WriteArgs::GetProxy()
{
    return m_prox;
}

void ilrd::WriteArgs::SetProxy(MasterProxy* prox)
{
    m_prox = prox;
}
