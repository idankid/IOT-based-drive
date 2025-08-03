/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-10
* \ <_. )	@Ex 
*  `---' 	@reviewer Shani				
************************************************/

#include <iostream>
#include "thread_pool.hpp"

namespace ilrd
{

    thread_local bool exit_thread = false;
    thread_local bool pause_thread = false;

/*--------------------- Threadpool----------------------------*/
ThreadPool::ThreadPool(int thread_num) : m_num_of_threads(thread_num),
 m_paused_threads(0), m_block(0), 
m_pause(new pauseTask()),m_close(new closeTask())
{
    for(int i = 0; i< thread_num; ++i)
    {
        std::shared_ptr<std::thread> t1(new std::thread(&ThreadPool::threadJob, this));
        m_threads.emplace(std::make_pair(t1->get_id(),t1));
    }
}

ThreadPool::~ThreadPool()
{
    for(int i = 0; i< m_num_of_threads; ++i)
    {
        AddTask(m_close, Priority::ADMIN_LOW);
    }

    m_paused_threads.release(m_num_of_threads);

    JoinThreads(m_num_of_threads);
}

void ThreadPool::Pause()
{
    for(int i = 0; i < m_num_of_threads; ++i)
    {
        AddTask(m_pause, Priority::ADMIN_HIGH);
    }

    for(int i = 0; i < m_num_of_threads; ++i)
    {
        m_block.acquire();
    }
}

void ThreadPool::Resume()
{
    m_paused_threads.release(m_num_of_threads);
}

void ThreadPool::AddTask(std::shared_ptr<thread_pool::ITPTask> task, Priority pri)
{
    TaskWrapper temp(task, pri);
    m_tasks.Push(temp);
}

void ThreadPool::SetNumOfThreads(int new_thread_num)
{
    int diff = new_thread_num - m_num_of_threads;
    for(int i = 0; i < diff; ++i)
    {
        std::shared_ptr<std::thread> t1(new std::thread(&ThreadPool::threadJob, this));
        m_threads.emplace(std::make_pair(t1->get_id(),t1));
    }
    for(int i = 0; i > diff; --i)
    {
        AddTask(m_close, Priority::ADMIN_HIGH);
    }

    if(diff < 0)
    {
        JoinThreads(-diff);
    }

    m_num_of_threads = new_thread_num;
}


/* ------------------------ thread job ---------------------------*/
void ThreadPool::threadJob()
{
    while(!exit_thread)
    {
        TaskWrapper task(NULL, Priority::LOW);
        m_tasks.Pop(task);
        task.GetPtr()->Run();

        if(pause_thread)
        {
            m_block.release();
            m_paused_threads.acquire();
            pause_thread = false;
        }
    }

    m_finished_threads.Push(std::this_thread::get_id());
}

void ThreadPool::JoinThreads(int num)
{
    for(int i = 0; i < num; ++i)
    {
        std::thread::id id;
        m_finished_threads.Pop(id);
        m_threads[id]->join();
        m_threads.erase(id);
    }
}


/* ------------------------ pause task ---------------------------*/
void ThreadPool::pauseTask::Run()
{
    pause_thread = true;
}

/* ------------------------ close task ---------------------------*/

void ThreadPool::closeTask::Run()
{
    exit_thread = true;
}

/* ------------------------ Task wrapper -----------------------------*/
std::shared_ptr<thread_pool::ITPTask> ThreadPool::TaskWrapper::GetPtr() const
{
    return m_peter;
}

ThreadPool::TaskWrapper::TaskWrapper(std::shared_ptr<thread_pool::ITPTask> ptr, Priority pri)
: m_priority(pri), m_peter(ptr)
{}

ThreadPool::TaskWrapper::~TaskWrapper()
{}

bool ThreadPool::TaskWrapper::operator<(const TaskWrapper& other) const
{
    return this->m_priority < other.m_priority;
}

/* ------------------------ function wrapper -----------------------------*/

thread_pool::FunctionTask::FunctionTask(std::function<void()> func) : m_func(func)
{}

thread_pool::FunctionTask::~FunctionTask()
{}

void thread_pool::FunctionTask::Run()
{
    m_func();
}
}