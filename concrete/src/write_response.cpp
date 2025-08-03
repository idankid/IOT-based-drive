/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-22
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <netinet/in.h>
#include "helper_funcs.hpp"
#include "write_response.hpp"


void ilrd::WriteResponse::OnSuccess(TaskResult res, Reply rep)
{
    (void)res;
    std::cout << "Write Success" << std::endl;
    rep.rep.error = htonl(0);
    Funcs::WriteAll(rep.fd, (char*)&rep.rep, sizeof(struct nbd_reply));
}

void ilrd::WriteResponse::OnFailure(TaskResult res, Reply rep)
{
    (void)res;
    std::cout << "Write Failure" << std::endl;
    rep.rep.error = htonl(1);
    Funcs::WriteAll(rep.fd, (char*)&rep.rep, sizeof(struct nbd_reply));
}