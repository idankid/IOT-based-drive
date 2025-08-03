/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-26
* \ <_. )	@Ex AsyncInjection
*  `---' 	@reviewer Gil		 	 				
************************************************/

#include <memory>   /* make_shared */
#include <handleton.hpp>
#include "AsyncInjection.hpp"

ilrd::AsyncInjection::AsyncInjection(std::function<bool(void)> func, 
                                    std::chrono::milliseconds interval)
: m_function(func), m_interval(interval), m_curr_task(new AsyncInjTask(*this)) 
{
    ilrd::Handleton<Scheduler>::GetInstance()->AddTask(m_curr_task, m_interval);
}

void ilrd::AsyncInjection::PerformAction()
{
    if(m_function())
    {
        ilrd::Handleton<Scheduler>::GetInstance()->AddTask(m_curr_task, m_interval);
    }
    else
    {
        delete this;
    }
}

ilrd::AsyncInjection::AsyncInjTask::AsyncInjTask(AsyncInjection& to_inject)
: m_inject(to_inject)
{}

void ilrd::AsyncInjection::AsyncInjTask::Run()
{
    m_inject.PerformAction();
}