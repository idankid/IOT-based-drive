/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-10
* \ <_. )	@Ex 
*  `---' 	@reviewer Shani	 	 				
************************************************/

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <semaphore>            /* std::semaphore*/   
#include <functional>           /* std::function */
#include <thread>
#include <unordered_map>   
#include "TPTasks.hpp"
#include "priority_queue.hpp"

namespace ilrd
{

class ThreadPool
{
public:
    enum class Priority
    {
        ADMIN_LOW = 0, //don't use it, it will break your code
        LOW = 1, 
        MID = 2, 
        HIGH = 3,
        ADMIN_HIGH = 4 //don't use it, it will break your code
    };


    /*---------------------- public methods ----------------------------*/
    ThreadPool(int thread_num = (std::thread::hardware_concurrency() - 1));
    ~ThreadPool();
    void AddTask(std::shared_ptr<thread_pool::ITPTask> task, Priority pri = Priority::MID);
    void SetNumOfThreads(int new_thread_num); //blocking
    void Pause();   //blocking 
    void Resume();

private:
    class TaskWrapper;
    void threadJob();
    void JoinThreads(int num);
    /*--------------------- containers ---------------------------*/
    PriorityQueue<TaskWrapper> m_tasks;
    WaitableQueue<std::thread::id> m_finished_threads;
    std::unordered_map<std::thread::id,std::shared_ptr<std::thread>> m_threads;
    int m_num_of_threads;

    /*------------------ pause / resume ---------------------*/
    std::counting_semaphore<> m_paused_threads;
    std::binary_semaphore m_block;

    class pauseTask : public thread_pool::ITPTask
    {
        void Run();
    };
    std::shared_ptr<thread_pool::ITPTask> m_pause;

    /*------------------- exit task -------------------------*/
    class closeTask : public thread_pool::ITPTask
    {
        void Run();
    };
    std::shared_ptr<thread_pool::ITPTask> m_close;

    /*--------------------- TaskWrapper -------------------------------*/
    class TaskWrapper
    {
    public:
        TaskWrapper(std::shared_ptr<thread_pool::ITPTask>, Priority pri);
        ~TaskWrapper();
        std::shared_ptr<thread_pool::ITPTask> GetPtr() const;
        bool operator<(const TaskWrapper& other) const;
    private:
        Priority m_priority;
        std::shared_ptr<thread_pool::ITPTask> m_peter;
    };
};

} //ilrd

#endif /*__THREAD_POOL_H__*/
