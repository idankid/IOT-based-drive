/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-23
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <iostream>
#include <unistd.h>     /* fork, pid_t */
#include <fcntl.h>      /* open*/
#include <sys/ioctl.h>  /* ioctl */
#include <sys/socket.h> /* socket_pair */
#include <linux/nbd.h>  /*NBD_... */
#include "NBD.hpp"

int ilrd::NBD::Init(const char* device_file, size_t device_size)
{
    int nbd_fd = open(device_file, O_RDWR);
    ioctl(nbd_fd, NBD_SET_SIZE, device_size);
    ioctl(nbd_fd, NBD_CLEAR_QUE);
    ioctl(nbd_fd, NBD_CLEAR_SOCK);

    //creating the sockets for NBD client and server
    int sp[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, sp);

    pid_t pid = fork();
    if (0 == pid)
    {
        close(sp[0]);

        //setting the NDB socket to be sp[1]
        ioctl(nbd_fd, NBD_SET_SOCK, sp[1]);
        
        // enabling NBD messages to be sent, it is blocking
        ioctl(nbd_fd, NBD_DO_IT);

        //cleanup
        ioctl(nbd_fd, NBD_CLEAR_QUE);
        ioctl(nbd_fd, NBD_CLEAR_SOCK);
        exit(0);
    }
    close(sp[1]);

    return sp[0];
}

struct nbd_request ilrd::NBD::GetRequest(int fd)
{
    struct nbd_request request;
	ssize_t bytes_read = read(fd, &request, sizeof(request));
    if(bytes_read == -1)
    {
        throw std::runtime_error("failed to read nbd request");
    }

    return request;
}