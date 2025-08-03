/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __TICKET_HPP__
#define __TICKET_HPP__

#include <mutex>
#include <memory>

#include "uid.hpp"
#include "ATaskArgs.hpp"
#include "command.hpp"
#include "Dispastcher.hpp"

namespace ilrd
{

struct TaskResult
{
    enum Status : bool 
    {
        SUCCESS = true,
        FAILURE = false
    };

    Status stat;
    UID uid;
    std::shared_ptr<char[]> data;
    int64_t len;
};

class Ticket : public std::enable_shared_from_this<Ticket>
{
public:
    enum class TicketStatus
    {
        NEW = 0,
        DONE = 1
    };

    Ticket(UID uid, int mode);
    UID GetUid() const;
    TicketStatus GetStat() const;
    TaskResult GetRes() const;
    void SetRes(TaskResult res);
    int GetMode() const;
    void SetMode(TicketStatus);
    void RegisterToTicket(ACallback<std::shared_ptr<Ticket>>* callback);
    void UnRegisterToTicket(ACallback<std::shared_ptr<Ticket>>* callback);
    void Notify();
private:
    UID m_uid;
    int m_mode;
    TaskResult m_res;
    TicketStatus m_stat;
    int m_count;
    std::mutex m_lock;
    Dispatcher<std::shared_ptr<Ticket>> m_ticket_dispatcher;
};

}//namespace ilrd

#endif /*__TICKET_HPP__*/
