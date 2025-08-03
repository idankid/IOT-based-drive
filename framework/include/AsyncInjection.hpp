/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-26
* \ <_. )	@Ex AsyncInjection
*  `---' 	@reviewer Gil		 	 				
************************************************/

#ifndef __ASYNCINJECTION_H__
#define __ASYNCINJECTION_H__

#include <functional>   /* std::function */

#include "scheduler.hpp" /* ISchedulerTask, Scheduler */

namespace ilrd
{

class AsyncInjection
{
public:
    //func: true to interval, false to delete
    AsyncInjection(std::function<bool(void)>, 
                        std::chrono::milliseconds interval);  
private:
    ~AsyncInjection() = default;

    std::function<bool(void)> m_function;
    std::chrono::milliseconds m_interval;
    
    class AsyncInjTask : public ISchedulerTask
    {
    public:
        AsyncInjTask(AsyncInjection&);
        void Run();
    private:
        AsyncInjection& m_inject;
    };
    
    std::shared_ptr<AsyncInjTask> m_curr_task;
    void PerformAction();
};

}//namespace ilrd

#endif /*__ASYNCINJECTION_H__*/
