/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __MINION_MANAGER_HPP__
#define __MINION_MANAGER_HPP__

#include <map>
#include <vector>
#include <memory>
#include <mutex>

#include "Dispastcher.hpp"
#include "i_minion_proxy.hpp"
#include "ticket.hpp"
#include "ATaskArgs.hpp"
#include "read_args.hpp"
#include "write_args.hpp"
#include "uid.hpp"
#include "input_proxy.hpp"

namespace ilrd
{
class MinionManager
{
public:
    MinionManager();
    ~MinionManager() = default;
    void AddReadTask(std::shared_ptr<ReadArgs> args);
    void AddWriteTask(std::shared_ptr<WriteArgs> args);
    void RegisterForNewTicket(ACallback<std::shared_ptr<Ticket>>* callback);
    void Init(std::vector<std::shared_ptr<IMinionProxy>>& minions);
private:
    std::vector<std::shared_ptr<IMinionProxy>> m_minions;
    Dispatcher<std::shared_ptr<Ticket>> m_new_ticket_dispatcher;
    std::map<UID, Ticket> m_tickets;
    std::mutex m_lock;

    size_t m_minion_size;
};

}//namespace ilrd

#endif /*__MINION_MANAGER_HPP__*/
