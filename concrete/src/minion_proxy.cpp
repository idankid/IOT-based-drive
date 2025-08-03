/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "message_read_request.hpp"
#include "message_write_request.hpp"
#include "message_read_response.hpp"
#include "message_write_response.hpp"
#include "handleton.hpp"
#include "factory.hpp"
#include "response_manager.hpp"
#include "ticket.hpp"
#include "minion_proxy.hpp"

ilrd::MinionProxy::MinionProxy(const char* ip, int port): m_ip(ip), m_port(port)
{
    Handleton<Factory<int32_t, TaskResult, std::shared_ptr<AMessage>>>::GetInstance()
                            ->Register(MessageType::READ_RESPONSE, 
    [](std::shared_ptr<AMessage>msg_)
    {
        std::shared_ptr<MessageReadResponse> msg =
                            std::static_pointer_cast<MessageReadResponse>(msg_);
        std::shared_ptr<TaskResult> res(new TaskResult);
        res->uid = msg->GetUID();
        res->stat = msg->GetStatus() ? TaskResult::Status::SUCCESS : TaskResult::Status::FAILURE;
        res->data = msg->GetData();
        res->len = msg->GetDataLen();

        return res;
    });

    Handleton<Factory<int32_t, TaskResult, std::shared_ptr<AMessage>>>::GetInstance()
                            ->Register(MessageType::WRITE_RESPOSE, 
    [](std::shared_ptr<AMessage>msg_)
    {
        std::shared_ptr<MessageWriteResponse> msg =
                            std::static_pointer_cast<MessageWriteResponse>(msg_);
        std::shared_ptr<TaskResult> res(new TaskResult);
        res->uid = msg->GetUID();
        res->stat = msg->GetStatus() ? TaskResult::Status::SUCCESS : TaskResult::Status::FAILURE;

        return res;
    });
}

ilrd::MinionProxy::~MinionProxy()
{
}

int ilrd::MinionProxy::GetMinionFD()
{
    return m_minion.GetFD();
}

void ilrd::MinionProxy::OnMinionWake(int fd, Mode mode)
{
    (void)mode;
    (void)fd;
    char recieved[BUFSIZ];
    m_minion.receive(recieved, BUFSIZ);

    char* to_parse = recieved;
    to_parse += sizeof(int32_t);
    
    int32_t type = *(int32_t*)to_parse;
    to_parse += sizeof(int32_t);
    
    std::shared_ptr<ilrd::AMessage> msg =  
        ilrd::Handleton<ilrd::Factory<int32_t, ilrd::AMessage>>::
                                        GetInstance()->Create(type);
    msg->Parse(to_parse);
    
    std::shared_ptr<TaskResult> res =
            Handleton<Factory<int32_t, TaskResult, std::shared_ptr<AMessage>>>::
                                            GetInstance()->Create(type, msg);

    std::shared_ptr<Ticket> ticket = Handleton<ResponseManager>::
                                        GetInstance()->GetTicket(msg->GetUID());

    if(ticket)
    {
        ticket->SetRes(*(res.get()));
    }
}

void ilrd::MinionProxy::AddWriteTask(UID id, size_t offset, size_t length, std::shared_ptr<char[]> data)
{
    std::shared_ptr<MessageWriteRequest> to_send(new 
                                MessageWriteRequest(id, offset, length, data));
    Send(to_send);
}

void ilrd::MinionProxy::AddReadTask(UID id, size_t offset, size_t length)
{
    std::shared_ptr<MessageReadRequest> to_send(new
                                         MessageReadRequest(id, offset, length));
    Send(to_send);
}

void ilrd::MinionProxy::Send(std::shared_ptr<AMessage> message)
{
    m_lock.lock();
    int32_t size = message->GetSize();
    std::unique_ptr<char[]> to_send(new char[size]);
    message->Stringify(to_send.get());
    m_minion.send(m_ip, m_port, to_send.get(), size);
    m_lock.unlock();
}