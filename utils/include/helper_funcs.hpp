/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-26
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __HELPER_FUNCS_HPP__
#define __HELPER_FUNCS_HPP__
#include <sys/types.h>

namespace ilrd::Funcs
{
    void ReadAll(int fd, char* buff, u_int32_t len);
    void WriteAll(int fd, char* buff, u_int32_t len);
}//namespace ilrd

#endif /*__HELPER_FUNCS_HPP__*/
