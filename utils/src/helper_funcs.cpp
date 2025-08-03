/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-26
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/
#include <unistd.h>
#include "helper_funcs.hpp"

void ilrd::Funcs::ReadAll(int fd, char* buff, u_int32_t len)
{
	int bytes_read;

	while (len > 0) {
	  bytes_read = read(fd, buff, len);
	  buff += bytes_read;
	  len -= bytes_read;
	}
}

void ilrd::Funcs::WriteAll(int fd, char* buff, u_int32_t len)
{
	int bytes_written;

	while (len > 0) {
	  bytes_written = write(fd, buff, len);
	  buff += bytes_written;
	  len -= bytes_written;
	}
}