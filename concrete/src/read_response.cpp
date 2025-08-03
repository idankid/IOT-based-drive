/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-22
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <netinet/in.h>
#include "read_response.hpp"
#include "helper_funcs.hpp"

void ilrd::ReadResponse::OnSuccess(TaskResult res, Reply rep)
{
    (void)res;

    rep.rep.error = htonl(0);
    Funcs::WriteAll(rep.fd, (char*)&rep.rep, sizeof(struct nbd_reply));
	Funcs::WriteAll(rep.fd,  res.data.get(), res.len);
    std::cout << "ReadSuccess -" <<  "the data is: '"<< res.data << "'" << std::endl;
}

void ilrd::ReadResponse::OnFailure(TaskResult res, Reply rep)
{
    (void)res;
    std::cout << "Read Failure" << std::endl;
    rep.rep.error = htonl(1);
    Funcs::WriteAll(rep.fd, (char*)&rep.rep, sizeof(struct nbd_reply));
}