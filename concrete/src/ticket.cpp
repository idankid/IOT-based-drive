/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "ticket.hpp"

ilrd::Ticket::Ticket(UID uid, int mode) : m_uid(uid), m_mode(mode), 
    m_stat(ilrd::Ticket::TicketStatus::NEW), m_count(0)
{}

ilrd::UID ilrd::Ticket::GetUid() const
{
    return m_uid;
}

int ilrd::Ticket::GetMode() const
{
    return m_mode;
}

ilrd::Ticket::TicketStatus ilrd::Ticket::GetStat() const
{
    return m_stat;
}

void ilrd::Ticket::SetMode(TicketStatus stat)
{
    m_stat = stat;
}

ilrd::TaskResult ilrd::Ticket::GetRes() const
{
    return m_res;
}

void ilrd::Ticket::SetRes(TaskResult res)
{
    m_lock.lock();
    
    if(m_count == 0 || m_res.stat == TaskResult::Status::FAILURE)
    {
        m_res = res;
    }
    
    if(++m_count == 2 || 
    (m_count == 1 && m_res.stat == TaskResult::SUCCESS && m_mode == Mode::READ))
    {
        SetMode(TicketStatus::DONE);
        Notify();
    }
    
    m_lock.unlock();
}

void ilrd::Ticket::RegisterToTicket(ACallback<std::shared_ptr<Ticket>>* callback)
{
    m_ticket_dispatcher.Register(callback);
}

void ilrd::Ticket::UnRegisterToTicket(ACallback<std::shared_ptr<Ticket>>* callback)
{
    m_ticket_dispatcher.Unregister(callback);
}

void ilrd::Ticket::Notify()
{
    m_ticket_dispatcher.Notify(shared_from_this());
}