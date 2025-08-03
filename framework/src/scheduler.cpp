/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-25
* \ <_. )	@Ex Scheduler
*  `---' 	@reviewer Liad		 	 				
************************************************/

#include <functional>

#include "scheduler.hpp"

void ilrd::Scheduler::TimerFunc(union sigval timer_data)
{
    Scheduler* data = static_cast<ilrd::Scheduler*>(timer_data.sival_ptr);
    data->m_thread_event();
}

timer_t ilrd::Scheduler::CreateTimer()
{
    struct sigevent signal_event = {};
    signal_event.sigev_notify = SIGEV_THREAD;
    signal_event.sigev_notify_function = &ilrd::Scheduler::TimerFunc;
    signal_event.sigev_value.sival_ptr = this;

    if(timer_create(CLOCK_REALTIME, &signal_event, &m_timer_id) != 0)
    {
        throw std::runtime_error("failed to create timer");
    }

    return m_timer_id;
}

ilrd::Scheduler::Scheduler() : m_timer_id(CreateTimer()), m_curr_task(nullptr),
    m_timer_time(), m_stop(false)
{}

ilrd::Scheduler::~Scheduler()
{
    std::unique_lock<std::mutex> lock(m_lock);
    m_cond.wait(lock, [this](){return std::atomic_load(&this->m_stop);});
    timer_delete(m_timer_id);
}

void ilrd::Scheduler::StartTimer()
{   
    time_t seconds = std::chrono::high_resolution_clock::to_time_t(m_task_time);
    long nano = (m_task_time - std::chrono::high_resolution_clock::from_time_t(seconds)).count();
    m_timer_time.it_value.tv_sec = seconds;
    m_timer_time.it_value.tv_nsec = nano; 
    
    timer_settime(m_timer_id, TIMER_ABSTIME, &m_timer_time, nullptr);
}


void ilrd::Scheduler::AddTask(std::shared_ptr<ISchedulerTask> task,
         std::chrono::milliseconds run_at_ms)
{
    std::chrono::high_resolution_clock::time_point when = 
        std::chrono::high_resolution_clock::now() + (run_at_ms);

    m_stop = false;
    std::unique_lock<std::mutex> lock(m_lock);
    if(when < m_task_time || !m_curr_task.get())
    {
        if(m_curr_task.get())
        {
            m_tasks.push(TaskWrapper(m_curr_task, m_task_time));
        }
        m_curr_task = task;
        m_task_time = when;
        StartTimer();
    }
    else
    {
        m_tasks.push(TaskWrapper(task, when));
    }
}


void ilrd::Scheduler::m_thread_event()
{
    m_lock.lock();
    std::shared_ptr<ilrd::ISchedulerTask> task = m_curr_task;
    m_lock.unlock();

    task->Run();
    
    std::unique_lock<std::mutex> lock(m_lock);
    if(!m_tasks.empty())
    {
        TaskWrapper task = m_tasks.top();
        m_tasks.pop();
        m_curr_task = task.m_task;
        m_task_time = task.m_time;
        
        StartTimer();
    }
    else
    {
        m_curr_task = nullptr;
        m_stop = true;
        m_cond.notify_one();
    }
}

ilrd::Scheduler::TaskWrapper::TaskWrapper(std::shared_ptr<ISchedulerTask> task,
    std::chrono::high_resolution_clock::time_point run_at_ms) : m_time(run_at_ms), m_task(task)
{}

bool ilrd::Scheduler::TaskWrapper::operator<(const ilrd::Scheduler::TaskWrapper& other) const
{
    return this->m_time > other.m_time;   
}