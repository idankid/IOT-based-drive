/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include <chrono>
#include <iostream>
#include <cstring>

#include "handleton.hpp"
#include "factory.hpp"
#include "read_args.hpp"
#include "write_args.hpp"
#include "response_manager.hpp"
#include "helper_funcs.hpp"
#include "NBD_proxy.hpp"

std::shared_ptr<ilrd::ITaskArgs> CreateReadArgs()
{
	std::shared_ptr<ilrd::ReadArgs> args(new ilrd::ReadArgs);
	return args;
}

std::shared_ptr<ilrd::ITaskArgs> CreateWriteArgs()
{
	std::shared_ptr<ilrd::WriteArgs> args(new ilrd::WriteArgs);
	return args;
}

ilrd::NBDProxy::NBDProxy()
{
	Handleton<Factory<int, ilrd::ITaskArgs>>::GetInstance()->
			Register(ilrd::Mode::READ, CreateReadArgs);
	Handleton<Factory<int, ilrd::ITaskArgs>>::GetInstance()->
			Register(ilrd::Mode::Write, CreateWriteArgs);

	m_fill_funcs[Mode::READ] = 
	[](std::shared_ptr<ITaskArgs> args_, struct nbd_request req, int fd)
	{
		std::shared_ptr<ReadArgs> args = std::static_pointer_cast<ReadArgs>(args_);
		args->SetLength(ntohl(req.len));
		args->SetOffset(be64toh(req.from));
		(void)fd;
	};

	m_fill_funcs[Mode::Write] = 
	[](std::shared_ptr<ITaskArgs> args_, struct nbd_request req, int fd)
	{
		std::shared_ptr<WriteArgs> args = std::static_pointer_cast<WriteArgs>(args_);
		u_int32_t len = ntohl(req.len);
		args->SetLength(len);
		args->SetOffset(be64toh(req.from));

		std::shared_ptr<char[]> buff(new char[len]);
		Funcs::ReadAll(fd, buff.get(),len);
		args->SetBuffer(buff);
	};
}

std::shared_ptr<ilrd::ITaskArgs> ilrd::NBDProxy::GetTaskArgs(int fd, ilrd::Mode mode)
{
	(void)mode;
	struct nbd_request req = NBD::GetRequest(fd);

    struct nbd_reply reply;
	reply.magic = htonl(NBD_REPLY_MAGIC);
	reply.error = htonl(0);
	memcpy(reply.handle, req.handle, sizeof(reply.handle));

	int type = ntohl(req.type);

	if(type == NBD_CMD_FLUSH  || type == NBD_CMD_TRIM)
	{
		std::cout << " flush / Trim" << std::endl;
		Funcs::WriteAll(fd, (char*)&reply, sizeof(struct nbd_reply));
		return nullptr;
	}

	std::shared_ptr<ITaskArgs> args = Handleton<Factory<int, ilrd::ITaskArgs>>::
										GetInstance()->Create(type);

	(m_fill_funcs[type])(args, req, fd);

	Reply rep;
	rep.fd = fd;
	rep.rep = reply;

	Handleton<ResponseManager>::GetInstance()->
				RegisterReply(((ATaskArgs*)args.get())->GetUid(), rep);

	return args;
}

void ilrd::NBDProxy::RegisterForNewTaskArgs(ACallback<ATaskArgs>* callback)
{
	m_dispatcher.Register(callback);
}