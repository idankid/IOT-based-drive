/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-06
* \ <_. )	@Ex 
*  `---' 	@reviewer 		 	 				
************************************************/

#ifndef __WAITABLE_QUEUE_H__
#define __WAITABLE_QUEUE_H__

#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace ilrd
{

template <typename T, class Queue = std::queue<T>>
class WaitableQueue
{
public:
    void Push(T data);
    bool Pop(std::chrono::milliseconds timeout, T& res);
    bool Pop(T& res);
    bool IsEmpty(); //gives the result for the asking time
protected:
    Queue m_container;
    std::timed_mutex m_lock;
    std::condition_variable_any m_cond;
};

template <typename T, class Queue>
void WaitableQueue<T, Queue>::Push(T data)
{
    m_lock.lock();

    m_container.push(data);
    
    m_lock.unlock();
    
    m_cond.notify_one();
}

template <typename T, class Queue>
bool WaitableQueue<T, Queue>::Pop(T& res)
{
    std::unique_lock<std::timed_mutex> lock(m_lock);
    m_cond.wait(lock, [this](){return !m_container.empty();});


    res = m_container.front();
    m_container.pop();

    return true;
}


template <typename T, class Queue>
bool WaitableQueue<T, Queue>::Pop(std::chrono::milliseconds timeout, T& res)
{
    auto before = std::chrono::high_resolution_clock::now();

    std::unique_lock<std::timed_mutex> lock(m_lock);
    m_lock.try_lock_for(timeout);

    auto after = std::chrono::high_resolution_clock::now();
    
    if(!m_cond.wait_for(lock, timeout - (after - before) , [this]()
                                        {
                                            return !this->m_container.empty();
                                        }))
    {
        return false;
    }
    
    res = m_container.front();
    m_container.pop();

    return true;
}


template <typename T, class Queue>
bool WaitableQueue<T, Queue>::IsEmpty()
{
    std::unique_lock<std::timed_mutex> lock(m_lock);
    return m_container.empty();
}

} //namespace ilrd


#endif /*__WAITABLE_QUEUE_H__*/
