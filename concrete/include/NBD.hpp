/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-23
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __NDB_HPP__
#define __NDB_HPP__

#include <netinet/in.h> /*ntohl*/
#include <cstring>      /* memcpy */
#include <linux/nbd.h>	/* nbd */
#include <unistd.h>     /* read */

namespace ilrd
{
class NBD
{
public:
    // dev_size must be divisible by 4096 
    static int Init(const char* devie_file, size_t device_size);
    static struct nbd_request GetRequest(int fd);
};

}//namespace ilrd

#endif /*__NDB_HPP__*/