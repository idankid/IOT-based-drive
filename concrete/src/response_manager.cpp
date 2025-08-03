/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/
#include <memory>

#include "handleton.hpp"
#include "factory.hpp"
#include "minion_manager.hpp"
#include "read_response.hpp"
#include "write_response.hpp"
#include "response_manager.hpp"

ilrd::ResponseManager::ResponseManager() : 
m_ticket_create_callback(*this, &ilrd::ResponseManager::OnNewTicket),
m_ticket_done_callback(*this, &ilrd::ResponseManager::OnTicketDone)
{
    Handleton<MinionManager>::GetInstance()->RegisterForNewTicket(&m_ticket_create_callback);
    Init();
}

void ilrd::ResponseManager::Init()
{
    Handleton<Factory<int, IResponse>>::GetInstance()->Register(Mode::READ, 
    []()
    {
        return std::shared_ptr<IResponse>(new ReadResponse());
    });
    Handleton<Factory<int, IResponse>>::GetInstance()->Register(Mode::Write,
    []()
    {
        return std::shared_ptr<IResponse>(new WriteResponse());
    });
}

void ilrd::ResponseManager::OnNewTicket(std::shared_ptr<Ticket> ticket)
{
    std::scoped_lock<std::mutex> lock(m_lock);

    if(ticket->GetStat() != Ticket::TicketStatus::NEW)
    {
        return;
    }

    m_tickets[ticket->GetUid()] = ticket;
    m_requests[ticket->GetUid()] = Handleton<Factory<int, IResponse>>::
                                GetInstance()->Create(ticket->GetMode());
    
    ticket->RegisterToTicket(&m_ticket_done_callback);

}

void ilrd::ResponseManager::OnTicketFailure(std::shared_ptr<Ticket> ticket)
{
    std::scoped_lock<std::mutex> lock(m_lock);
    Reply rep = m_replies[ticket->GetUid()];
    m_requests[ticket->GetUid()]->OnFailure(ticket->GetRes(), rep);

    ticket->UnRegisterToTicket(&m_ticket_done_callback);
    m_requests.erase(ticket->GetUid());
    m_tickets.erase(ticket->GetUid());
    m_replies.erase(ticket->GetUid());
}

void ilrd::ResponseManager::OnTicketDone(std::shared_ptr<Ticket> ticket)
{
    std::scoped_lock<std::mutex> lock(m_lock);
    Reply rep = m_replies[ticket->GetUid()];

    if(ticket->GetRes().stat == TaskResult::Status::SUCCESS)
    {
        m_requests[ticket->GetUid()]->OnSuccess(ticket->GetRes(), rep);
    }
    else
    {
        m_requests[ticket->GetUid()]->OnFailure(ticket->GetRes(), rep);
    }

    ticket->UnRegisterToTicket(&m_ticket_done_callback);
    m_requests.erase(ticket->GetUid());
    m_tickets.erase(ticket->GetUid());
    m_replies.erase(ticket->GetUid());
}

std::shared_ptr<ilrd::Ticket> ilrd::ResponseManager::GetTicket(UID id)
{
    std::scoped_lock<std::mutex> lock(m_lock);
    return m_tickets[id];
}

void ilrd::ResponseManager::RegisterReply(UID id, Reply rep)
{
    std::scoped_lock<std::mutex> lock(m_lock);
    m_replies[id] = rep;
}
