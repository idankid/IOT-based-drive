/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-23
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/
#include <memory>
#include <iostream>

#include "handleton.hpp"
#include "response_manager.hpp"
#include "ticket.hpp"
#include "check_functor.hpp"

ilrd::CheckFunctor::CheckFunctor(UID id) : m_uid(id), 
m_start(std::chrono::system_clock::now())
{}

bool ilrd::CheckFunctor::operator()()
{
    std::shared_ptr<Ticket> ticket = Handleton<ResponseManager>::
											GetInstance()->GetTicket(m_uid);
    if(!ticket)
    {
        return false;
    }

    if(ticket->GetStat() == Ticket::TicketStatus::DONE)
    {
        ticket->Notify();
        return false;
    }

    if(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - 
        std::chrono::system_clock::to_time_t(m_start) > 5)
    {
        std::cout << "timeout" << std::endl;
        Handleton<ResponseManager>::GetInstance()->OnTicketFailure(ticket);
        return false;
    }
    
    return true;
}