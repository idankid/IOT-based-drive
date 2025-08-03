/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-25
* \ <_. )	@Ex Scheduler
*  `---' 	@reviewer Liad	 	 				
************************************************/

#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <condition_variable> 
#include <mutex>        /* mutex */
#include <chrono>       /* chrono */
#include <signal.h>     /* sigev, timer, and more... */
#include <functional>   /* std::functional */
#include <memory>       /* shared_ptr */
#include <queue>        /* priority_queue */

namespace ilrd
{

class ISchedulerTask
{
public:
    virtual void Run() = 0;
};

class Scheduler
{
public:
    Scheduler();
    ~Scheduler();
    void AddTask(std::shared_ptr<ISchedulerTask>, std::chrono::milliseconds run_at_ms);
private:
    static void TimerFunc(union sigval timer_data);
    timer_t CreateTimer();
    void StartTimer();
    void  m_thread_event();

    timer_t m_timer_id;

    std::shared_ptr<ISchedulerTask> m_curr_task;
    std::chrono::high_resolution_clock::time_point m_task_time;
    struct itimerspec m_timer_time;

    std::mutex m_lock;
    std::atomic<bool> m_stop;
    std::condition_variable_any m_cond;

    class TaskWrapper
    {
    public:
        TaskWrapper(std::shared_ptr<ISchedulerTask>,
                std::chrono::high_resolution_clock::time_point run_at_ms);
        ~TaskWrapper() = default;
        bool operator<(const ilrd::Scheduler::TaskWrapper& other) const;
        std::chrono::high_resolution_clock::time_point m_time;
        std::shared_ptr<ISchedulerTask> m_task;
    };

    std::priority_queue<TaskWrapper> m_tasks;
};
    
} // namespace ilrd


#endif /*__SCHEDULER_HPP__*/
