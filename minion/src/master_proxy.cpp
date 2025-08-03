/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-20
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "handleton.hpp"
#include "factory.hpp"
#include "message_read_request.hpp"
#include "message_read_response.hpp"
#include "message_write_request.hpp"
#include "message_write_response.hpp"
#include "master_proxy.hpp"
#include "minion_read_args.hpp"
#include "minion_write_args.hpp"

ilrd::MasterProxy::MasterProxy(int port)
{
    m_master.bind(port);
    
    m_fill_funcs[READ_REQUEST] = [this](std::shared_ptr<ITaskArgs> to_fill, 
        std::shared_ptr<ilrd::AMessage> msg_)
        {
            ReadArgs* args = static_cast<ReadArgs*>(to_fill.get());
            MessageReadRequest* msg = static_cast<MessageReadRequest*>(msg_.get());
            args->SetUID(msg->GetUID());
            args->SetLength(msg->GetLength());
            args->SetOffset(msg->GetOffset());
            args->SetProxy(this);
        };

    m_fill_funcs[WRITE_REQUEST] = [this](std::shared_ptr<ITaskArgs> to_fill, 
        std::shared_ptr<ilrd::AMessage> msg_)
        {
            WriteArgs* args = static_cast<WriteArgs*>(to_fill.get());
            MessageWriteRequest* msg = static_cast<MessageWriteRequest*>(msg_.get());
            args->SetUID(msg->GetUID());
            args->SetLength(msg->GetLength());
            args->SetOffset(msg->GetOffset());
            args->SetBuffer(msg->GetBuffer());
            args->SetProxy(this);
        };

    InitFactories();
}

void ilrd::MasterProxy::InitFactories()
{
    ilrd::Handleton<ilrd::Factory<int32_t, AMessage>>::GetInstance()->
        Register(READ_REQUEST, []()
        {
            return std::shared_ptr<AMessage>(new MessageReadRequest());
        });
    ilrd::Handleton<ilrd::Factory<int32_t, AMessage>>::GetInstance()->
        Register(WRITE_REQUEST, []()
        {
            return std::shared_ptr<AMessage>(new MessageWriteRequest());
        });
    ilrd::Handleton<Factory<int, ITaskArgs>>::GetInstance()->Register(READ_REQUEST, []()
        {
            return std::shared_ptr<ITaskArgs>(new ReadArgs());
        });
    ilrd::Handleton<Factory<int, ITaskArgs>>::GetInstance()->Register(WRITE_REQUEST, []()
        {
            return std::shared_ptr<ITaskArgs>(new WriteArgs());
        });
}

int ilrd::MasterProxy::GetFd()
{
    return m_master.GetFD();
}

std::shared_ptr<ilrd::ITaskArgs> ilrd::MasterProxy::GetTaskArgs(int fd, Mode mode)
{
    (void) mode;
    (void) fd;

    char recieved[BUFSIZ];
    m_master.receive(recieved, BUFSIZ);

    char* to_parse = recieved;
    to_parse += sizeof(int32_t);
    
    int32_t type = *(int32_t*)to_parse;
    to_parse += sizeof(int32_t);
    
    std::shared_ptr<ilrd::AMessage> msg =  
        ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::
                                        GetInstance()->Create(type);
    msg->Parse(to_parse);

    std::shared_ptr<ITaskArgs> to_return = 
        ilrd::Handleton<Factory<int, ITaskArgs>>::GetInstance()->Create(type);

    (m_fill_funcs[type])(to_return, msg);
    return to_return;
}

void ilrd::MasterProxy::SendReadResponse(UID id, bool status,
                                    std::shared_ptr<char[]> buffer, int64_t len)
{
    m_lock.lock();
    
    MessageReadResponse res(id, status, buffer, len);
    std::shared_ptr<char[]> to_send(new char[res.GetSize()]);
    res.Stringify(to_send.get());
    m_master.send(to_send.get(), res.GetSize());
    
    m_lock.unlock();
}

void ilrd::MasterProxy::SendWriteResponse(UID id, bool status)
{
    m_lock.lock();

    MessageWriteResponse res(id, status);
    std::shared_ptr<char[]> to_send(new char[res.GetSize()]);
    res.Stringify(to_send.get());
    
    m_master.send(to_send.get(), res.GetSize());
    m_lock.unlock();

}