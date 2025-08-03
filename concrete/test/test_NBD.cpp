/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-23
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <sys/select.h>
#include <cstddef>
#include <memory>
#include <netinet/in.h> /*ntohl*/
#include <cstring>      /* memcpy */
#include <linux/nbd.h>	/* nbd */
#include <unistd.h>     /* read */
#include <iostream> 	

#include "NBD.hpp"

#define MB (1024 *1024)

// Terminal B – run this compiled executable:
const std::size_t dev_size = 4 * MB; // NBD needs at least 4MB virtual drive.
char g_VirtualDisk[dev_size]; // dev_size must be divisible by 4096


static int read_all(int fd, char* buf, size_t count)
{
  int bytes_read;

  while (count > 0) {
    bytes_read = read(fd, buf, count);
    buf += bytes_read;
    count -= bytes_read;
  }
  return 0;
}

static int write_all(int fd, char* buf, size_t count)
{
  int bytes_written;

  while (count > 0) {
    bytes_written = write(fd, buf, count);
    buf += bytes_written;
    count -= bytes_written;
  }
  return 0;
}

void HandleNBDRead(int fd, u_int64_t from, u_int32_t len, struct nbd_reply reply)
{
	reply.error = htonl(0/*SUCCESS*/);
	// buff is our concrete buffer, read it from our virtual disk 
	// READ buff FROM VIRTUAL DISK;
	// Respond to NBD:
	// - write_all() implementation same as in BUSE 
	// - Respond with status (success / fail):
	write_all(fd, (char*)&reply, sizeof(struct nbd_reply));
	// - Respond with the buffer which was read:
	write_all(fd,  g_VirtualDisk + from, len);
	std::cout << "Reading: " << std::endl;
	write(1, &g_VirtualDisk[from], len);

}

void HandleNBDWrite(int nbd_fd, u_int64_t from, u_int32_t len,std::shared_ptr<char[]> buff, struct nbd_reply reply)
{
	// WRITE TO VIRTUAL DISK;
	memcpy(&g_VirtualDisk[from], buff.get(), len);
	reply.error = htonl(0/*SUCCESS*/);

	std::cout << "Writing" << std::endl;
	write(1, &g_VirtualDisk[from], len);

	// Respond to NBD:
	// - write_all() implementation same as in BUSE 
	// - Respond with status (success / fail):
	write_all(nbd_fd, (char*)&reply, sizeof(struct nbd_reply));
}

//goes to ndb proxy
void OnNBDMessage(int nbd_fd)
{
	// Read NBD request
	struct nbd_request request;
	ssize_t bytes_read = read(nbd_fd, &request, sizeof(request));
	
    // Setup reply:
	struct nbd_reply reply;
	reply.magic = htonl(NBD_REPLY_MAGIC);
	reply.error = htonl(0);
	memcpy(reply.handle, request.handle, sizeof(reply.handle));
	// Translate network to host:

	u_int32_t len = ntohl(request.len);
	u_int64_t from = be64toh(request.from);
	// Handle read / write differently:
	switch(ntohl(request.type))
	{
	case NBD_CMD_READ:
		HandleNBDRead(nbd_fd,from, len, reply);
		break;
	case NBD_CMD_WRITE:
		std::shared_ptr<char[]> chunk = std::shared_ptr<char[]>(new char[len]);
		// read_all() - as implemented in BUSE 
		read_all(nbd_fd, chunk.get(),len);
		HandleNBDWrite(nbd_fd,from, len, chunk, reply);
		break;
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 1;
	}

	ilrd::NBD nbd;
	int fd = nbd.Init(argv[1], 4*1024*1024);

	fd_set read_set;
	fd_set write_set;
	
	while (true)
    {
		FD_ZERO(&read_set);
		FD_ZERO(&write_set);
		FD_SET(fd, &read_set);
		FD_SET(fd, &write_set);
		
        select(fd + 1, &read_set, &write_set, nullptr, nullptr);
		if(FD_ISSET(fd, &read_set) || FD_ISSET(fd, &read_set))
		{
			OnNBDMessage(fd);
		}
    }

	return 0;
}

