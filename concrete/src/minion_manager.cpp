/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-04-07
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#include "handleton.hpp"
#include "Reactor.hpp"
#include "minion_manager.hpp"
#include "read_args.hpp"
#include "write_args.hpp"

ilrd::MinionManager::MinionManager() : m_minion_size(4*1024*1024)
{}

void ilrd::MinionManager::Init(std::vector<std::shared_ptr<IMinionProxy>>& minions)
{
    for(auto i : minions)
    {
        Handleton<Reactor>::GetInstance()->Register(i->GetMinionFD(), ilrd::Mode::READ,
                [i](int fd, Mode mode)
                {
                    i->OnMinionWake(fd, mode); 
                });
            
        m_minions.push_back(i);
    }
}

void ilrd::MinionManager::AddReadTask(std::shared_ptr<ReadArgs> args)
{
    if(!args)
    {
        return;
    } 

    std::shared_ptr<Ticket> ticket(new Ticket(args->GetUid(), args->GetKey()));
    m_new_ticket_dispatcher.Notify(ticket);

    size_t index = args->GetOffset() / m_minion_size;
    size_t inner_offset = args->GetOffset() % m_minion_size;
    
    try
    {
        std::scoped_lock<std::mutex> lock(m_lock);
        m_minions[index]->AddReadTask(args->GetUid() ,inner_offset, args->GetLength());
        m_minions[(index + 1) % m_minions.size()]->
            AddReadTask(args->GetUid(), inner_offset + m_minion_size, args->GetLength());
    }
    catch(...)
    {
        //todo add logs
    }
}

void ilrd::MinionManager::AddWriteTask(std::shared_ptr<WriteArgs> args)
{
    if(!args)
    {
        return;
    } 

    std::shared_ptr<Ticket> ticket(new Ticket(args->GetUid(), args->GetKey()));
    m_new_ticket_dispatcher.Notify(ticket);

    size_t index = args->GetOffset() / m_minion_size;
    size_t inner_offset = args->GetOffset() % m_minion_size;
    
    try
    {
        std::scoped_lock<std::mutex> lock(m_lock);
        m_minions[index]->AddWriteTask(args->GetUid() ,inner_offset, args->GetLength(), args->GetBuffer());
        m_minions[(index + 1) % m_minions.size()]->
            AddWriteTask(args->GetUid(), inner_offset + m_minion_size, args->GetLength(), args->GetBuffer());
    }
    catch(...)
    {
        //todo add logs
    }
}

void ilrd::MinionManager::RegisterForNewTicket(ACallback<std::shared_ptr<Ticket>>* callback)
{
    m_new_ticket_dispatcher.Register(callback);
}