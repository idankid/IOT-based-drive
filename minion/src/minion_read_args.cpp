/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "minion_read_args.hpp"

ilrd::ReadArgs::ReadArgs(size_t offset, size_t length): ATaskArgs(offset, length)
{}

int ilrd::ReadArgs::GetKey()
{
	return (int)ilrd::READ;
}

ilrd::MasterProxy* ilrd::ReadArgs::GetProxy()
{
    return m_prox;
}

void ilrd::ReadArgs::SetProxy(MasterProxy* prox)
{
    m_prox = prox;
}
