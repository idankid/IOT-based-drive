/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-08
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __RESPONSE_MANAGER_HPP__
#define __RESPONSE_MANAGER_HPP__

#include <map>
#include <mutex>

#include "i_response.hpp"
#include "ticket.hpp"
#include "ATaskArgs.hpp"
#include "uid.hpp"
#include "types.hpp"

namespace ilrd
{

class ResponseManager
{
public:
    ResponseManager();    
    ~ResponseManager() = default;
    std::shared_ptr<Ticket> GetTicket(UID id);
    void OnTicketFailure(std::shared_ptr<Ticket> ticket);
    void RegisterReply(UID, Reply);
private:
    void Init();
    void OnNewTicket(std::shared_ptr<Ticket> ticket);
    void OnTicketDone(std::shared_ptr<Ticket> ticket);
    Callback<ResponseManager, std::shared_ptr<Ticket>> m_ticket_create_callback;
    Callback<ResponseManager, std::shared_ptr<Ticket>> m_ticket_done_callback;
    std::map<UID, std::shared_ptr<IResponse>> m_requests;
    std::map<UID, std::shared_ptr<Ticket>> m_tickets;
    std::map<UID, Reply> m_replies;
    std::mutex m_lock;
};

}//namespace ilrd

#endif /*__RESPONSE_MANAGER_HPP__*/
