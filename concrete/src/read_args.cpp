/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "read_args.hpp"


ilrd::ReadArgs::ReadArgs(size_t offset, size_t length): ATaskArgs(offset, length)
{}

int ilrd::ReadArgs::GetKey()
{
	return (int)ilrd::READ;
}

