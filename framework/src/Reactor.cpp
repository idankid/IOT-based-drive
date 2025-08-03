/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-24
* \ <_. )	@Ex Reactor
*  `---' 	@reviewer Gil		 	 				
************************************************/

#include <algorithm>    /* std::for_each */
#include "Reactor.hpp"

ilrd::Reactor::Reactor(std::shared_ptr<IListener> listener) 
: m_listener(listener) , m_is_running(false)
{}

void ilrd::Reactor::Register(int fd, Mode mode,
                            std::function<void(int, Mode)> callback)
{
    m_callbacks[std::make_pair(fd, mode)] = callback;
}

void ilrd::Reactor::UnRegister(int fd, Mode mode)
{
    try
    {
        m_callbacks.erase(std::make_pair(fd, mode));
    }
    catch(...)
    {}
}

void ilrd::Reactor::Run()
{
    m_is_running = true;

    while(m_is_running)
    { 
        std::vector<std::pair<int, ilrd::Mode>> to_listen(m_callbacks.size());

        std::transform(m_callbacks.begin(), m_callbacks.end(), to_listen.begin(),
                [](std::pair<std::pair<int, ilrd::Mode>, 
                    std::function<void(int, ilrd::Mode)>> curr) 
                { 
                    return curr.first;
                });
    
        std::vector<std::pair<int, Mode>> 
            to_activate = m_listener->Listen(to_listen);

        std::for_each(to_activate.begin(), to_activate.end(), 
            [this](std::pair<int, Mode> curr)
        {
            this->m_callbacks[curr](curr.first, curr.second);
        });
    }
}

void ilrd::Reactor::Stop()
{
    m_is_running = false;
}


